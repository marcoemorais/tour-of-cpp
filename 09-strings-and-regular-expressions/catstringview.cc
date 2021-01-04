// Demonstrate operations in std::string_view.
#include <string>
#include <string_view>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"


// cat concatenates from a pair of string_view.
// Advantages.
// 1. Doesn't require const reference, points to c-style strings ok.
// 2. Ok to pass temporaries such as returned from std::string::substr.
std::string cat(std::string_view sv1, std::string_view sv2)
{
    std::string result{sv1};
    result += " ";
    result += sv2;
    return result;
}

TEST_CASE("[catstringview]")
{
    using namespace std::string_literals; // Required.
    using namespace std::string_view_literals; // Required.

    // Concatenate pair of string_view.
    auto rcv1 =cat("Harry"sv, "Potter"sv); // sv is a string_view literal.
    REQUIRE(rcv1 == "Harry Potter"s);

    // Concatenate mix of string_view and string.
    auto rcv2 = cat("Harry"sv, "Potter II"s);
    REQUIRE(rcv2 == "Harry Potter II"s);

    // Concatenate string.
    auto rcv3 = cat("Harry"s, "Potter III"s);
    REQUIRE(rcv3 == "Harry Potter III"s);

    // Concatenate c-style strings.
    auto rcv4 = cat("Harry", "Potter IV");
    REQUIRE(rcv4 == "Harry Potter IV"s);

    // Concatenate (pointer,length) pair.
    std::string harry_potter{"Harry Potter"};
    auto rcv5 = cat({&harry_potter[0], 5}, {&harry_potter[6], 6});
    REQUIRE(rcv5 == "Harry Potter"s);
}
