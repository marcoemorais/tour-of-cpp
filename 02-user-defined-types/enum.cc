// Demonstrate `enum class` and use of operator overloading with enum.
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

enum class Color { red, blue, green };
enum class Traffic_light { green, yellow, red };

// operator++ mimics the sequence of a traffic light.
Traffic_light& operator++(Traffic_light& tl)
{
    switch (tl) {
        case Traffic_light::red:
            return tl = Traffic_light::green;
        case Traffic_light::yellow:
            return tl = Traffic_light::red;
        case Traffic_light::green:
        default:
            return tl = Traffic_light::yellow;
    }
}

TEST_CASE("[enum_class]")
{

    Color rgb1 = Color::green; // Requires scope.
    REQUIRE(int(rgb1) == 2); // Cast required to convert enum to int.
    REQUIRE(Color::blue == Color{1}); // Cast required to convert int to enum.

    Color rgb2 = Color::green;
    REQUIRE(rgb1 == rgb2); // Enum class provides overloaded operator==.
}

TEST_CASE("[enum_operator++]")
{
    Traffic_light tl = Traffic_light::green;

    ++tl;
    REQUIRE(tl == Traffic_light::yellow);

    ++tl;
    REQUIRE(tl == Traffic_light::red);

    ++tl;
    REQUIRE(tl == Traffic_light::green);
}
