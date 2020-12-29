#include <istream>
#include <sstream>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

struct entry
{
    std::string name;
    int value;
};

// read_entry reads name and value from input stream.
entry read_entry(std::istream& is)
{
    std::string name;
    int value;
    is >> name >> value;
    return {name, value}; // Bind variables to return type.
}

TEST_CASE("[binding]")
{
    {
        std::istringstream is("foo 10");
        auto rcv = read_entry(is); // Standard return-by-value.
        REQUIRE(rcv.name == "foo");
        REQUIRE(rcv.value == 10);
    }

    {
        std::istringstream is("bar 100");
        auto [name, value] = read_entry(is); // Unpack.
        REQUIRE(name == "bar");
        REQUIRE(value == 100);
    }
}
