// Implement function template equivalent to std::accumulate.
#include <cstdint>
#include <iterator>
#include <numeric>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// Wrap in mystd to avoid collison with std::accumulate.
namespace mystd {

// accumulate returns the sum of the elements in range [first, last).
template <typename FwdIter, typename T = typename std::iterator_traits<FwdIter>::value_type>
T accumulate(FwdIter first, FwdIter last, T value)
{
    while (first != last) {
        value += *first;
        ++first;
    }
    return value;
}

}

TEST_CASE("[accumulate]")
{
    SUBCASE("Sum with 0 initial value")
    {
        std::vector<int> v1{1,2,3,4,5};
        auto rcv = mystd::accumulate(std::begin(v1), std::end(v1), 0);
        REQUIRE(rcv == 15);
    }

    SUBCASE("Sum with nonzero initial value")
    {
        std::vector<int> v1{1,2,3,4,5};
        auto rcv = mystd::accumulate(std::begin(v1), std::end(v1), 10);
        REQUIRE(rcv == 25);
    }

    SUBCASE("Accumulator has different type from input")
    {
        std::vector<std::uint8_t> v1{128, 64, 64, 32, 32}; // Overflow if accumulate as uint8_t.
        int init{0};
        auto rcv = mystd::accumulate(std::begin(v1), std::end(v1), init);
        REQUIRE(rcv == 320);
    }

    SUBCASE("Compare to std::accumulate")
    {
        std::vector<double> v1{2.5, -7.5, 2.5};
        double init{2.5};
        auto rcv = accumulate(std::begin(v1), std::end(v1), init);
        auto expected = std::accumulate(std::begin(v1), std::end(v1), init);
        REQUIRE(rcv == expected);
    }
}
