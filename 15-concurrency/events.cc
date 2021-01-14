// Demonstrate use of std::condition_variable for communicating events to listeners.
#include <array>
#include <functional>
#include <future>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <numeric>
#include <thread>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

class EventSource
{
public:
    EventSource() = default;
    EventSource(const EventSource&) = delete;
    EventSource& operator=(const EventSource&) = delete;

    // listen attaches a one-time callback function to events from this source.
    void listen(int id, std::function<void(int)> func)
    {
        // handler_func invokes the callback after trigger.
        // NOTE: Capture `this` and refer to members without this.
        auto handler_func = [this](int id, std::function<void(int)> func, std::promise<void> started){
            std::unique_lock lck{m};
            started.set_value(); // Thread started, lock acquired, about to wait.
            cond.wait(lck);      // Unlock and wait for notification.
            func(id);            // Invoke callback.
        };

        // Start a thread waiting for next event.
        std::promise<void> started;
        std::future<void> started_future = started.get_future();
        callbacks.emplace_back(handler_func, id, func, std::move(started));

        // Wait until thread is started before returning.
        started_future.wait();
    }

    // trigger notifies all listeners of event.
    void trigger()
    {
        // Acquire the lock before notification to avoid race with listener.
        std::unique_lock lck{m};
        cond.notify_all();
    }

    // wait waits for all listener callbacks to finish.
    void wait()
    {
        for (std::size_t i = 0; i < callbacks.size(); ++i) {
            callbacks[i].join();
        }
    }

private:
    std::condition_variable cond;
    std::mutex m;
    std::vector<std::thread> callbacks;
};

TEST_CASE("[events]")
{
    constexpr int num_listeners = 10;
    std::array<int, num_listeners> notified = {0}; // Initialize unset.

    // callback_func is invoked as a result of event.
    auto callback_func = [&notified](int id){
        notified[id] = 1; // No synchronization required.
    };

    // EventSource is responsible for notifying listeners.
    EventSource events;

    // Start a thread for each listener waiting for notification.
    for (int id = 0; id != num_listeners; ++id) {
        events.listen(id, callback_func);
    }

    // Notify all listeners.
    events.trigger();

    // Wait for callbacks to finish.
    events.wait();

    auto sum = std::accumulate(std::begin(notified), std::end(notified), 0);
    REQUIRE(sum == num_listeners);
    for (int id = 0; id != num_listeners; ++id) {
        REQUIRE(notified[id] == 1);
    }
}
