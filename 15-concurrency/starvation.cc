// Demonstrate thread starvation between greedy and polite worker threads.
#include <functional>
#include <chrono>
#include <mutex>
#include <thread>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

using namespace std::chrono_literals;

TEST_CASE("[starvation]")
{
    // Simulation runtime and shared memory lock.
    constexpr std::chrono::seconds runtime = 10s;
    std::mutex m;

    // worker_thread repeatedly locks a mutex while performing some work.
    auto worker_thread = [&runtime, &m] (std::chrono::nanoseconds wait, int num_wait, int& work_count) {
        auto begin = std::chrono::steady_clock::now();
        while ((std::chrono::steady_clock::now() - begin) < runtime) {
            for (int i = 0; i != num_wait; ++i) {
                // Acquire and hold lock for wait interval.
                std::scoped_lock<std::mutex> guard{m};
                std::this_thread::sleep_for(wait);
            }
            ++work_count;
        }
    };

    // greedy worker acquires lock 1 time for 10ns = 10ns/work.
    std::chrono::nanoseconds greedy_wait = 10ns;
    int greedy_num_wait = 1;
    int greedy_work_count = 0;

    // polite worker acquires lock 10 times for 1ns = 10ns/work.
    std::chrono::nanoseconds polite_wait = 1ns;
    int polite_num_wait = 10;
    int polite_work_count = 0;

    std::thread greedy_worker{worker_thread, greedy_wait, greedy_num_wait, std::ref(greedy_work_count)};
    std::thread polite_worker{worker_thread, polite_wait, polite_num_wait, std::ref(polite_work_count)};

    greedy_worker.join();
    polite_worker.join();

    // Output from 5 repetitions:
    // values: REQUIRE( 3341 <  12708 )
    // values: REQUIRE( 3313 <  12634 )
    // values: REQUIRE( 3299 <  10778 )
    // values: REQUIRE( 3573 <  11217 )
    // values: REQUIRE( 3212 <  14695 )
    REQUIRE(polite_work_count < greedy_work_count);
}
