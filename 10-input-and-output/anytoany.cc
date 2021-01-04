// Demonstrate use of std::stringstream for any-to-any conversion.
#include <cmath>
#include <istream>
#include <sstream>
#include <stdexcept>
#include <string>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

template <typename Target = std::string, typename Source = std::string>
Target to(Source arg)
{
    std::stringstream interpreter;
    Target result;

    if (!(interpreter << arg)                   // Interpreter reads source.
        || !(interpreter >> result)             // Interpreter writes target.
        || !(interpreter >> std::ws).eof()) {   // Interpreter not at eof.
        throw std::runtime_error("to<>() failed");
    }

    return result;
}

struct entry
{
    std::string name;
    int value;
};

// operator>> deserializes entry from std::istream.
std::istream& operator>>(std::istream& is, entry& e)
{
    is >> e.name;
    is >> e.value;
    return is;
}

TEST_CASE("[anytoany]")
{
    // Convert from std::string to int.
    std::string in1("2020");
    int out1 = to<int>(in1);
    REQUIRE(out1 == 2020);

    // Convert from double to std::string.
    double in2 = 2.*std::acos(0.);
    std::string out2 = to<std::string>(in2);
    REQUIRE(out2 == "3.14159");

    // Convert from std::string to entry using overloaded operator>>.
    std::string in3("foo 99");
    auto out3 = to<entry>(in3);
    REQUIRE(out3.name == "foo");
    REQUIRE(out3.value == 99);
}
