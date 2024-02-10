// Span is a (pointer,count) pair with support for range-based for loop.
#include <cstddef>
#include <memory>
#include <numeric>
#include <functional>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// Span captures pointer-and-count for range-based for loop.
template <typename T>
struct Span
{
    Span() = default;

    Span(T* p, std::size_t count)
        : p(p)
        , count(count)
    { }

    ~Span() = default; // Span doesn't own any resource.

    T* p = nullptr;
    std::size_t count = 0;
};

// begin satisfies requirements for range-based for loop.
template <typename T>
T* begin(Span<T>& s)
{
    return s.p;
}

// end satisfies requirements for range-based for loop.
template <typename T>
T* end(Span<T>& s)
{
    return s.count > 0 ? s.p+s.count : nullptr;
}

// cbegin satisfies requirements for range-based for loop.
template <typename T>
const T* cbegin(const Span<T>& s)
{
    return s.p;
}

// cend satisfies requirements for range-based for loop.
template <typename T>
const T* cend(const Span<T>& s)
{
    return s.count > 0 ? s.p+s.count : nullptr;
}

TEST_CASE("[Span]")
{
    // One use-case for Span is to wrap a C-style array.
    constexpr std::size_t N = 100;
    std::unique_ptr<int, std::function<void(int*)>> a1(
        static_cast<int*>(std::malloc(sizeof(int)*N)),
        [](int* pa) { std::free(pa); } // Invoke when exiting scope.
    );
    int *pa1 = a1.get();
    for (std::size_t i = 0; i < N; ++i) {
        pa1[i] = int(i)+1;
    }

    SUBCASE("Range-based for loop, non-const reference")
    {
        Span s{pa1, N};
        int i = 1;

        for (auto& v : s) {
            REQUIRE(v == i++);
        }
    }

    SUBCASE("Range-based for loop, const reference")
    {
        Span s{pa1, N};
        int i = 1;

        for (const auto& v : s) {
            REQUIRE(v == i++);
        }
    }

    SUBCASE("Use begin/end with algorithm")
    {
        Span s{pa1, N};
        auto sum = std::accumulate(begin(s), end(s), 0);
        auto expected = N*(N+1)/2;
        REQUIRE(sum == expected);
    }
}
