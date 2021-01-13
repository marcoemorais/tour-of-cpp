// Demonstrate initializing std::thread with function and functor.
#include <iostream>
#include <mutex>
#include <thread>

std::mutex cout_mutex;

void hello()
{
    std::lock_guard<std::mutex> guard(cout_mutex);
    std::cout << "Hello (function)\n";
}

struct Hello
{
    void operator()()
    {
        std::lock_guard<std::mutex> guard(cout_mutex);
        std::cout << "Hello (functor)\n";
    }
};

int main()
{
    std::thread t1{hello};   // Function.
    std::thread t2{Hello{}}; // Functor.

    t1.join();
    t2.join();
}
