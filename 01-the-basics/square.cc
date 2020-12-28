#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

constexpr double square(double x)
{
    return x*x;
}

TEST_CASE("[square]")
{
    struct test_case
    {
        double input;
        double expected;
    };

    std::vector<test_case> test_cases{
        {0.0, 0.0},
        {1.0, 1.0},
        {2.0, 4.0},
        {3.0, 9.0}
    };

    for (const auto& c : test_cases) {
        auto rcv = square(c.input);
        CAPTURE(c.input);
        CAPTURE(rcv);
        CAPTURE(c.expected);
        REQUIRE(rcv == doctest::Approx(c.expected));
    }

    // Compile-time expression.
    constexpr double four_square = square(4.0);
    REQUIRE(four_square == doctest::Approx(16.0));
}
