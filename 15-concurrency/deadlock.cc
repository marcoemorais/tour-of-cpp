// Demonstrate use of scoped_lock with pairs of locks to avoid deadlock.
#include <functional>
#include <mutex>
#include <string>
#include <thread>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// Message provides thread-safe comparison of message.
class Message
{
public:
    Message(const std::string& body)
        : body(body)
    { }

    friend bool safe_equal(const Message& m1, const Message& m2);
    friend bool unsafe_equal(const Message& m1, const Message& m2);

private:
    mutable std::mutex m;
    std::string body;
};

// thread-safe comparison of messages.
bool safe_equal(const Message& m1, const Message& m2)
{
    // To avoid deadlock, acquire both locks.
    std::scoped_lock guard{m1.m, m2.m};
    return m1.body == m2.body;
}

// thread-unsafe comparison of messages.
bool unsafe_equal(const Message& m1, const Message& m2)
{
    // Acquiring locks separately is only safe when messages passed in consistent order.
    std::scoped_lock guard1{m1.m};
    std::scoped_lock guard2{m2.m};
    return m1.body == m2.body;
}

TEST_CASE("[deadlock]")
{
    // thread_func compares shared memory messages.
    auto thread_func = [] (int num_repeat, const Message& m1, const Message& m2, bool safe) {
        while (num_repeat > 0) {
            if (safe) {
                static_cast<void>(safe_equal(m1, m2));   // Ignore return value.
            } else {
                static_cast<void>(unsafe_equal(m1, m2)); // Ignore return value.
            }
            --num_repeat;
        }
    };

    constexpr int num_repeat = 1'000'000;

    SUBCASE("safe=true")
    {
        // Messages to compare, content or result of comparison doesn't matter.
        Message m1{"hello"};
        Message m2{"world"};

        // Use thread-safe comparison.
        bool safe = true;

        SUBCASE("order=consistent")
        {
            // Pass messages in consistent order: t1=(m1,m2), t2=(m1,m2)
            std::thread t1{thread_func, num_repeat, std::cref(m1), std::cref(m2), safe};
            std::thread t2{thread_func, num_repeat, std::cref(m1), std::cref(m2), safe};

            t1.join();
            t2.join();

            REQUIRE(true == true); // Reached without deadlock.
        }

        SUBCASE("order=inconsistent")
        {
            // Pass messages in inconsistent order: t1=(m1,m2), t2=(m2,m1)
            std::thread t1{thread_func, num_repeat, std::cref(m1), std::cref(m2), safe};
            std::thread t2{thread_func, num_repeat, std::cref(m2), std::cref(m1), safe};

            t1.join();
            t2.join();

            REQUIRE(true == true); // Reached without deadlock.
        }
    }

    SUBCASE("safe=false")
    {
        // Messages to compare, content or result of comparison doesn't matter.
        Message m1{"hello"};
        Message m2{"world"};

        // Use thread-unsafe comparison.
        bool safe = false;

        SUBCASE("order=consistent")
        {
            // Pass messages in consistent order: t1=(m1,m2), t2=(m1,m2)
            std::thread t1{thread_func, num_repeat, std::cref(m1), std::cref(m2), safe};
            std::thread t2{thread_func, num_repeat, std::cref(m1), std::cref(m2), safe};

            t1.join();
            t2.join();

            REQUIRE(true == true); // Reached without deadlock.
        }

        // Passing messages in inconsistent order using thread-unsafe comparison will deadlock.
    }
}
