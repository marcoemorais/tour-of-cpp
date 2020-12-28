#include <vector>
#include <numeric>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

TEST_CASE("[init]")
{
    double d1 = 2.3;
    REQUIRE(d1 == 2.3);

    double d2{2.3};
    REQUIRE(d2 == 2.3);

    double d3 = {2.3};
    REQUIRE(d3 == 2.3);

    std::vector<int> v1 = {1,2,3};
    REQUIRE(v1 == std::vector<int>{1,2,3});

    std::vector<int> v2{1,2,3};
    REQUIRE(v2 == std::vector<int>{1,2,3});

    std::vector<int> v3(3);
    std::iota(std::begin(v3), std::end(v3), 1);
    REQUIRE(v3 == std::vector<int>{1,2,3});
}
