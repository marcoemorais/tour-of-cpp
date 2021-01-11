// Demonstrate use of std::pair and std::tuple.
#include <string>
#include <utility>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

using namespace std::string_literals; // Required.

TEST_CASE("[pairtuple]")
{
    SUBCASE("pair")
    {
        // Use forwarding to construct pair and deduce type from parameters.
        std::pair p1{"hello"s, 3.14};
        REQUIRE(p1.first == "hello"s);
        REQUIRE(p1.second == 3.14);

        // Use factory function to construct pair.
        auto p2 = std::make_pair("world"s, 42);
        REQUIRE(p2.first == "world"s);
        REQUIRE(p2.second == 42);
    }

    SUBCASE("tuple")
    {
        // Use forwarding to construct tuple and deduce type from parameters.
        std::tuple t1{"hello"s, 3.14, 1'000};
        REQUIRE(std::get<0>(t1) == "hello"s);
        REQUIRE(std::get<1>(t1) == 3.14);
        REQUIRE(std::get<2>(t1) == 1'000);

        // Use factory function to construct tuple.
        auto t2 = std::make_tuple("world"s, 6.28, 1'000'000);
        REQUIRE(std::get<0>(t2) == "world"s);
        REQUIRE(std::get<1>(t2) == 6.28);
        REQUIRE(std::get<2>(t2) == 1'000'000);

        // Replace components.
        std::get<0>(t2) += "!";
        REQUIRE(std::get<0>(t2) == "world!"s);

        // Use binding to unpack tuple.
        auto [a, b, c] = t1;
        REQUIRE(a == "hello"s);
        REQUIRE(b == 3.14);
        REQUIRE(c == 1'000);
    }
}
