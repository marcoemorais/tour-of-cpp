// Demonstrate different ways to insert into a unordered_map.
#include <string>
#include <unordered_map>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

using namespace std::string_literals; // Required.

TEST_CASE("[mapinsert]")
{
    std::unordered_map<std::string, std::string> m1{
        {"k1"s, "v1"s},
        {"k2"s, "v2"s},
    };

    REQUIRE(m1.size() == 2);
    REQUIRE(m1["k1"s] == "v1"s);
    REQUIRE(m1["k2"s] == "v2"s);

    // Use unordred_map::insert to copy the k-v pair into map.
    m1.insert({"k3"s, "v3"s});
    REQUIRE(m1["k3"s] == "v3"s);

    // Use unordered_map::emplace to construct the k-v pair in map.
    m1.emplace("k4"s, "v4"s);
    REQUIRE(m1["k4"s] == "v4"s);

    // Use operator[] to insert non-default value.
    m1["k5"s] = "v5"s;
    REQUIRE(m1["k5"s] == "v5"s);

    // operator[] will insert an element into map if not already present.
    REQUIRE(m1.count("k6"s) == 0);
    std::string v6(m1["k6"]); // Side-effect is insert.
    REQUIRE(m1.count("k6"s) == 1);
    REQUIRE(m1["k6"s] == ""s);
}
