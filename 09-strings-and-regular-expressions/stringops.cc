// Demonstrate operations in std::string.
#include <string>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

TEST_CASE("[stringops]")
{
    using namespace std::string_literals; // Required.

    SUBCASE("substr")
    {
        std::string hello{"Hello world"};

        // substr takes parameters: pos, size
        REQUIRE(hello.substr(0, hello.size()) == hello);
        // Not an error for size to extend past end of string.
        REQUIRE(hello.substr(0, hello.size()+10) == hello);
        // Not an error for substr to be empty.
        REQUIRE(hello.substr(0, 0) == std::string{});
    }

    SUBCASE("replace")
    {
        // NOTE: Unlike substr which returns new string, replace returns *this.

        // replace with same size substring.
        std::string hello1{"Hello world"};
        REQUIRE(hello1.replace(0, 5, "12345") == "12345 world"s);

        // replace with smaller substring.
        std::string hello2{"Hello world"};
        REQUIRE(hello2.replace(0, 5, "123") == "123 world"s);

        // replace with larger substring.
        std::string hello3{"Hello world"};
        REQUIRE(hello3.replace(0, 5, "1234567") == "1234567 world"s);
    }

    SUBCASE("conversions")
    {
        std::string s1{"10"};
        REQUIRE(std::stoi(s1) == 10);

        std::string s2{"3.14"};
        REQUIRE(std::stod(s2) == 3.14);

        int x = 20;
        REQUIRE(std::to_string(x) == "20"s);

        double y = 6.0;
        REQUIRE(std::to_string(y) == "6.000000"s); // Uses %f conversion.
    }
}
