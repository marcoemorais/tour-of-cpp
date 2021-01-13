// Demonstrate use of mutex for sharing counter across threads.
#include <mutex>
#include <thread>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// Counter is a thread-safe counter.
class Counter
{
public:
    void safe_incr()
    {
        std::scoped_lock<std::mutex> guard(m);
        ++count;
    }

    void unsafe_incr()
    {
        ++count;
    }

    int value() const
    {
        std::scoped_lock<std::mutex> guard(m);
        return count;
    }

private:
    mutable std::mutex m;
    int count = 0;
};

TEST_CASE("[counter]")
{
    // thread_func increments a shared memory counter.
    auto thread_func = [] (Counter& c, int num_repeat, bool safe) {
        while (num_repeat > 0) {
            if (safe) {
                c.safe_incr();
            } else {
                c.unsafe_incr();
            }
            --num_repeat;
        }
    };

    constexpr int num_threads = 10;
    constexpr int num_repeat = 1'000'000;
    constexpr int expected_count = num_threads*num_repeat;

    SUBCASE("safe=true")
    {
        // counter will be incremented by all threads.
        Counter counter;

        // Use thread-safe increment.
        bool safe = true;

        // Start the workers, note that start is not synchronized.
        std::vector<std::thread> workers;
        for (int i = 0; i != num_threads; ++i) {
            // Use thread variadic constructor to pass parameters to function.
            workers.emplace_back(thread_func, std::ref(counter), num_repeat, safe);
        }

        // Wait for each worker to perform num_repeat increments.
        for (int i = 0; i != num_threads; ++i) {
            workers[i].join();
        }

        REQUIRE(counter.value() == expected_count);
    }

    SUBCASE("safe=false")
    {
        // counter will be incremented by all threads.
        Counter counter;

        // Use thread-unsafe increment.
        bool safe = false;

        // Start the workers, note that start is not synchronized.
        std::vector<std::thread> workers;
        for (int i = 0; i != num_threads; ++i) {
            // Use thread variadic constructor to pass parameters to function.
            workers.emplace_back(thread_func, std::ref(counter), num_repeat, safe);
        }

        // Wait for each worker to perform num_repeat increments.
        for (int i = 0; i != num_threads; ++i) {
            workers[i].join();
        }

        REQUIRE(counter.value() != expected_count);
    }
}
