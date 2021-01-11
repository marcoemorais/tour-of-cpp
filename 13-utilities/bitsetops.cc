// Demonstrate operations in std::bitset.
#include <bitset>
#include <string>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

using namespace std::string_literals; // Required.

TEST_CASE("[bitsetops]")
{
    SUBCASE("init")
    {
        // Construct from string of 1/0.
        std::bitset<9> bs1{"110001111"};
        REQUIRE(bs1.to_ullong() == 399UL);

        // Construct from string literal.
        std::bitset<9> bs2{0b1'1000'1111};
        REQUIRE(bs2.to_ullong() == 399UL);

        // Construct from unsigned long.
        std::bitset<9> bs3{399UL};
        REQUIRE(bs2.to_string() == "110001111"s);
    }

    SUBCASE("count")
    {
        std::bitset<9> bs1{"110001111"};
        REQUIRE(bs1.count() == 6);
    }

    SUBCASE("bitwise")
    {
        std::bitset<9> bs1{"110001111"};
        auto bs2 = ~bs1; // Complement all bits.

        // Set all bits.
        auto bs3 = bs1 | bs2;
        REQUIRE(bs3.to_string() == "111111111"s);

        // Unset all bits.
        auto bs4 = bs1 & bs2;
        REQUIRE(bs4.to_string() == "000000000"s);

        // Shift bits.
        auto bs5 = bs1 << 2;
        REQUIRE(bs5.to_string() == "000111100"s);
    }
}
