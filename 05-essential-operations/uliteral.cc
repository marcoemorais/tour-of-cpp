// Demonstrate creating user-defined literals.
#include <cmath>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// D2R converts from degrees to radians.
constexpr double operator""_D2R(long double deg)
{
    constexpr double pi = 2.*std::acos(0.);
    return deg * pi / 180.;
}

// R2D converts from radians to degrees.
constexpr double operator""_R2D(long double rad)
{
    constexpr double pi = 2.*std::acos(0.);
    return rad * 180. / pi;
}

TEST_CASE("[uliteral]")
{
    // Demonstrate user-defined literals for converting radians<>degree.
    auto halfpi = 90._D2R;
    CAPTURE(halfpi);
    REQUIRE(halfpi == doctest::Approx(1.5707963));

    auto quarterpi = 45._D2R;
    CAPTURE(quarterpi);
    REQUIRE(quarterpi == doctest::Approx(0.7853981));

    auto ninety = 1.5707963_R2D;
    CAPTURE(ninety);
    REQUIRE(ninety == doctest::Approx(90.));

    auto fortyfive = 0.7853981_R2D;
    CAPTURE(fortyfive);
    REQUIRE(fortyfive == doctest::Approx(45.));
}
