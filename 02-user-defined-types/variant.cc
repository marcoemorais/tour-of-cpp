// Demonstrate std::variant as an improvment of `union`.
#include <variant>
#include <string>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

TEST_CASE("[variant]")
{
    std::variant<int, std::string> v1;
    v1 = 1; // Assign int.

    CAPTURE(v1);
    REQUIRE(std::get<int>(v1) == 1);
    REQUIRE(std::get<0>(v1) == 1);

    // Acccessing unset alternatives raises exception.
    REQUIRE_THROWS_AS(std::get<std::string>(v1), std::bad_variant_access);
    REQUIRE_THROWS_AS(std::get<1>(v1), std::bad_variant_access);

    v1 = "Hello"; // Assign string.
    CAPTURE(v1);
    REQUIRE(std::get<std::string>(v1) == "Hello");
    REQUIRE(std::get<1>(v1) == "Hello");

    // Acccessing unset alternatives raises exception.
    REQUIRE_THROWS_AS(std::get<int>(v1), std::bad_variant_access);
    REQUIRE_THROWS_AS(std::get<0>(v1), std::bad_variant_access);
}
