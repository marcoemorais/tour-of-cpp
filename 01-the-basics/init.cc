// Various forms of literal initialization.
#include <map>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

TEST_CASE("[init]")
{
    SUBCASE("scalar")
    {
        // Copy initialization.
        double d1 = 2.3;
        REQUIRE(d1 == 2.3);

        // Direct initialization using braced-init-list.
        double d2{2.3};
        REQUIRE(d2 == 2.3);

        // Copy initialization from braced-init-list.
        double d3 = {2.3};
        REQUIRE(d3 == 2.3);
    }

    SUBCASE("string")
    {
        std::string hello("Hello world");

        // const char*
        std::string s1 = "Hello world";
        REQUIRE(s1 == hello);

        // brace initialization.
        std::string s2{"Hello world"};
        REQUIRE(s2 == hello);

        // string literal using operator""s.
        using namespace std::string_literals; // Required.
        std::string s3 = "Hello world"s;
        REQUIRE(s3 == hello);
    }

    SUBCASE("vector")
    {
        std::vector<int> v1 = {1,2,3};
        REQUIRE(v1 == std::vector<int>{1,2,3});

        // Construct using std::initializer_list.
        std::vector<int> v2{1,2,3};
        REQUIRE(v2 == std::vector<int>{1,2,3});

        std::vector<int> v3(3);
        std::iota(std::begin(v3), std::end(v3), 1);
        REQUIRE(v3 == std::vector<int>{1,2,3});
    }

    SUBCASE("map")
    {
        std::map<std::string, int> m1{
            {"one", 1},
            {"two", 2},
            {"three", 3}
        };
        REQUIRE(m1.size() == 3);
        REQUIRE(m1["one"] == 1);
        REQUIRE(m1["two"] == 2);
        REQUIRE(m1["three"] == 3);
    }

    SUBCASE("pair")
    {
        using namespace std::string_literals; // Required.

        std::pair<std::string, int> p1{"one"s, 1};
        REQUIRE(p1.first == "one"s);
        REQUIRE(p1.second == 1);

        // Use forwarding to construct pair and deduce type from parameters.
        auto p2 = std::make_pair("two"s, 2);
        REQUIRE(p2.first == "two"s);
        REQUIRE(p2.second == 2);

        // Use argument type deduction to determine template type.
        std::pair p3{"three"s, 3};
        REQUIRE(p3.first == "three"s);
        REQUIRE(p3.second == 3);
    }
}
