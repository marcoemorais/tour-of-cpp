// set_ops demonstrates union, intersection, and (symmetric)difference.
#include <algorithm>
#include <iterator>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

TEST_CASE("[union]")
{
    std::vector<int> a = {1, 2, 3};
    std::vector<int> b = {2, 3, 4};

    std::vector<int> c;
    std::set_union(std::begin(a), std::end(a),
                   std::begin(b), std::end(b),
                   std::back_inserter(c));
    REQUIRE(c == std::vector<int>{1, 2, 3, 4}); // A U B
}

TEST_CASE("[intersection]")
{
    std::vector<int> a = {1, 2, 3};
    std::vector<int> b = {2, 3, 4};

    std::vector<int> c;
    std::set_intersection(std::begin(a), std::end(a),
                          std::begin(b), std::end(b),
                          std::back_inserter(c));
    REQUIRE(c == std::vector<int>{2, 3}); // A ^ B
}

TEST_CASE("[difference]")
{
    std::vector<int> a = {1, 2, 3};
    std::vector<int> b = {2, 3, 4};

    std::vector<int> c;
    std::set_difference(std::begin(a), std::end(a),
                        std::begin(b), std::end(b),
                        std::back_inserter(c));
    REQUIRE(c == std::vector<int>{1}); // A \ B
}

TEST_CASE("[symmetric_difference]")
{
    std::vector<int> a = {1, 2, 3};
    std::vector<int> b = {2, 3, 4};

    std::vector<int> c;
    std::set_symmetric_difference(std::begin(a), std::end(a),
                                  std::begin(b), std::end(b),
                                  std::back_inserter(c));
    REQUIRE(c == std::vector<int>{1, 4}); // (A \ B) U (B \ A)
}
