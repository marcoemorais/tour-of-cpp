#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

TEST_CASE("[ref]")
{
    int x = 1;
    int& rx = x;

    // x contains 1 and rx points to x.
    REQUIRE(x == 1);
    REQUIRE(rx == x);

    // assign to x through rx.
    rx = 2;
    REQUIRE(x == 2);
    REQUIRE(rx == 2);
}
