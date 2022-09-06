// partial_sum implements cumsum and factorial.
#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

TEST_CASE("[cumsum]")
{
    // Verify cumsum of 1..5.
    std::vector<int> a(5), b(5);
    std::iota(std::begin(a), std::end(a), 1);
    std::partial_sum(std::begin(a), std::end(a),
                     std::begin(b),
                     std::plus());
    REQUIRE(b == std::vector<int>{1, 3, 6, 10, 15});
}

TEST_CASE("[factorial]")
{
    // Verify factorial of 1..5.
    std::vector<int> a(5), b(5);
    std::iota(std::begin(a), std::end(a), 1);
    std::partial_sum(std::begin(a), std::end(a),
                     std::begin(b),
                     std::multiplies());
    REQUIRE(b == std::vector<int>{1, 2, 6, 24, 120});
}
