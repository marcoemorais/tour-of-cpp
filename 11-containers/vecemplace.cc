// Demonstrate use of template forwarding for emplace into container.
#include <string>
#include <utility>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

using namespace std::string_literals; // Required.

TEST_CASE("[vecemplace]")
{
    using Entry = std::pair<std::string, int>;
    std::vector<Entry> v1;

    v1.emplace_back("one"s, 1); // No braces, build a pair in v1.
    REQUIRE(v1[0] == std::pair{"one"s, 1});

    v1.push_back({"two"s, 2}); // Brace construct pair, copy to v1.
    REQUIRE(v1[1] == std::pair{"two"s, 2});
}
