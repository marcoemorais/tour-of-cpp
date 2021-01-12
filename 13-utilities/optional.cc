// Demonstrate use of std::optional.
#include <optional>
#include <string>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

using namespace std::string_literals; // Required.

TEST_CASE("[std::optional]")
{
    auto opt_func = [](bool b) -> std::optional<std::string> {
        return b
            ? std::optional<std::string>{"true"s}
            : std::nullopt; // Empty optional.
    };

    auto rcv1 = opt_func(true);
    REQUIRE(bool(rcv1) == true);
    REQUIRE(*rcv1 == "true"s);
    REQUIRE(rcv1.value_or("empty"s) == "true"s);

    auto rcv2 = opt_func(false);
    REQUIRE(bool(rcv2) == false);
    REQUIRE(rcv2.value_or("empty"s) == "empty"s);
}
