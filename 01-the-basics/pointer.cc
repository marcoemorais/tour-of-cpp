#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

TEST_CASE("[pointer]")
{
    int x = 1;
    int y = 2;
    int *px = &x;
    int *py = &y;

    // x contains 1 and px points to x.
    REQUIRE(x == 1);
    REQUIRE(*px == x);

    // y contains 2 and py points to y.
    REQUIRE(y == 2);
    REQUIRE(*py == y);

    // py points to x.
    py = px;
    REQUIRE(*py == x);

    // assign to x through py.
    *py = 3;
    REQUIRE(x == 3);
    REQUIRE(*px == 3);
}
