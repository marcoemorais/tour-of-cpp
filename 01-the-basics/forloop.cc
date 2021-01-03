// Demonstrate different forms of for-range syntax for array/vector containers.
#include <cstddef>
#include <iostream>

void for_i()
{
    int v[] = {0,1,2,3,4}; // Compiler allocates 5 elements based on {...}.
    constexpr std::size_t vsz = sizeof(v)/sizeof(v[0]); // Size known at compile-time.

    for (auto i = 0; i != vsz; ++i) {
        std::cout << "v[" << i << "]=" << v[i] << "\n";
    }
}

void for_range1()
{
    for (auto i : {10,11,12,13,14}) {
        std::cout << "i=" << i << "\n";
    }
}

void for_range2()
{
    int v[] = {20,21,22,23,24};

    // Use copy of element of v.
    for (auto x : v) {
        std::cout << "x=" << x << "\n";
    }
}

void for_range3()
{
    int v[] = {30,31,32,33,34};

    // Use reference to element of v.
    for (auto& x : v) {
        std::cout << "xref=" << x << "\n";
    }
}

void for_range4()
{
    int v[] = {40,41,42,43,44};

    // Use const reference to element of v.
    for (const auto& x : v) {
        std::cout << "cref=" << x << "\n";
    }
}

int main()
{
    for_i();
    for_range1();
    for_range2();
    for_range3();
    for_range4();
}
