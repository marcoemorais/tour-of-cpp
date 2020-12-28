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
}
