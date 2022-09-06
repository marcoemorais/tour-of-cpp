// all_any_none_of demonstrates logical algorithms using bind.
#include <algorithm>
#include <functional>
#include <iterator>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

TEST_CASE("[all_of]")
{
    std::vector<int> v = {1, 2, 3};

    // Verify all_of > 0 is true.
    {
        const int K = 0;
        auto result =
            all_of(begin(v), end(v),
                   std::bind(std::greater(), std::placeholders::_1, K));
        REQUIRE(result == true);
    }

    // Verify all_of > 2 is false.
    {
        const int K = 2;
        auto result =
            all_of(begin(v), end(v),
                   std::bind(std::greater(), std::placeholders::_1, K));
        REQUIRE(result == false);
    }

    // Verify all_of > 4 is false.
    {
        const int K = 4;
        auto result =
            all_of(begin(v), end(v),
                   std::bind(std::greater(), std::placeholders::_1, K));
        REQUIRE(result == false);
    }
}

TEST_CASE("[any_of]")
{
    std::vector<int> v = {1, 2, 3};

    // Verify any_of > 0 is true.
    {
        const int K = 0;
        auto result =
            any_of(begin(v), end(v),
                   std::bind(std::greater(), std::placeholders::_1, K));
        REQUIRE(result == true);
    }

    // Some any_of > 2 is true.
    {
        const int K = 2;
        auto result =
            any_of(begin(v), end(v),
                   std::bind(std::greater(), std::placeholders::_1, K));
        REQUIRE(result == true);
    }

    // Verify any_of > 4 is false.
    {
        const int K = 4;
        auto result =
            any_of(begin(v), end(v),
                   std::bind(std::greater(), std::placeholders::_1, K));
        REQUIRE(result == false);
    }
}

TEST_CASE("[none_of]")
{
    std::vector<int> v = {1, 2, 3};

    // Verify none_of > 0 is false.
    {
        const int K = 0;
        auto result =
            none_of(begin(v), end(v),
                    std::bind(std::greater(), std::placeholders::_1, K));
        REQUIRE(result == false);
    }

    // Verify none_of > 2 is false.
    {
        const int K = 2;
        auto result =
            none_of(begin(v), end(v),
                    std::bind(std::greater(), std::placeholders::_1, K));
        REQUIRE(result == false);
    }

    // Verify none_of > 4 is true.
    {
        const int K = 3;
        auto result =
            none_of(begin(v), end(v),
                    std::bind(std::greater(), std::placeholders::_1, K));
        REQUIRE(result == true);
    }
}
