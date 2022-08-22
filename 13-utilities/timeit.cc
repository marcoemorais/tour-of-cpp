// Demonstrate use of std::chrono for microbenchmarking.
#include <chrono>
#include <iostream>
#include <thread>

using namespace std::chrono_literals;

int main()
{
    auto t1 = std::chrono::steady_clock::now();
    std::this_thread::sleep_for(5s); // Duration literal.
    auto t2 = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration<double, std::milli>(t2-t1).count();
    std::cout << "elapsed: " << elapsed_ms << "ms\n";
}
