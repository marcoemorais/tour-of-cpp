// Demonstrate basic reference operations and distinction from pointers.
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

    // Cannot reassign to a const reference.
    int y1 = 3, y2 = 4;
    const int& cry = y1;
    REQUIRE(cry == 3);
    //cry = y2; // Forbidden.
    rx = y2;    // OK.
    REQUIRE(rx == 4);
    REQUIRE(x == 4); // Also changed the thing rx referred to.
}
