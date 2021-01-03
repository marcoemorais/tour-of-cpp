// Literal intiailization that emphasizes readability.
#include <bitset>
#include <string>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

TEST_CASE("[literal]")
{
    // Binary literal.
    int eight = 0b1000;
    REQUIRE(eight == 8);

    // Use ' to make long literals more readable.
    int million = 1'000'000;
    REQUIRE(million == doctest::Approx(1e6));

    // String literal.
    using namespace std::string_literals; // Required.
    std::string one = "one"s;
    REQUIRE(one == std::string{"one"});

    // Array of bits.
    std::bitset<8> b1{"10000000"};
    REQUIRE(b1.to_ulong() == 128U);
}
