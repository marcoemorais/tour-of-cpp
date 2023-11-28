// Demonstrate operations in std::regex.
#include <istream>
#include <iterator>
#include <regex>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// is_ssn demonstrates use of std::regex_match to match SSN.
bool is_ssn(std::string_view sv)
{
    static std::regex pat{R"(\d{3}-\d{2}-\d{4})"}; // Raw string syntax.
    return std::regex_match(std::begin(sv), std::end(sv), pat);
}

// read_ssn demonstrates use of std::regex_iterator to return SSN from stream.
std::vector<std::string> read_ssn(std::istream& is)
{
    static std::regex pat{R"(\d{3}-\d{2}-\d{4})"}; // Raw string syntax.

    std::vector<std::string> results;
    for (std::string line; std::getline(is, line); ) {
        // Find and append all ssn appearing on the line to results.
        auto mbegin = std::sregex_iterator(std::begin(line), std::end(line), pat);
        auto mend = std::sregex_iterator{};
        for (auto m = mbegin; m != mend; ++m) {
            results.push_back((*m).str());
        }
    }

    return results;
}

TEST_CASE("[std::regex_match]")
{
    using namespace std::string_view_literals; // Required.

    struct test_case
    {
        std::string_view input;
        bool expected;
    };

    std::vector<test_case> test_cases = {
        // Exact match.
        {
            "123-12-1234"sv,
            true
        },
        // regex_match assumes leading (^) and trailing anchor ($) on pattern.
        {
            " 123-12-1234"sv,
            false
        },
        // regex_match assumes leading (^) and trailing anchor ($) on pattern.
        {
            "123-12-1234 "sv,
            false
        },
        // Substring match is also not accepted.
        {
            "123-12-1234 hello world"sv,
            false
        },
    };

    for (const auto& c : test_cases) {
        auto rcv = is_ssn(c.input);
        CAPTURE(c.input);
        REQUIRE(rcv == c.expected);
    }
}

TEST_CASE("[std::regex_iterator]")
{
    using namespace std::string_literals; // Required.

    std::istringstream is(
        "header line\n"
        "111-11-1111\n"             // Same as std::regex_match.
        " 222-22-2222 \n"           // Leading and trailing whitespace.
        "hello 333-33-3333 world\n" // Leading and trailing non-match chars.
        "444-44-4444 555-55-5555\n" // Multiple matches on same line.
        "last line\n"
    );

    std::vector<std::string> expected{
        "111-11-1111"s,
        "222-22-2222"s,
        "333-33-3333"s,
        "444-44-4444"s,
        "555-55-5555"s,
    };

    auto rcv = read_ssn(is);
    REQUIRE(rcv.size() == expected.size());
    REQUIRE(rcv == expected);
}

TEST_CASE("[std::regex_replace]")
{
    // Pattern to match leading or trailing space.
    std::regex leading_or_trailing_space{R"(^\s+|\s+$)"};

    struct test_case
    {
        std::string input;
        std::string expected;
    };

    std::vector<test_case> test_cases{
        // No leading or trailing space.
        {
            "hello",
            "hello",
        },
        // Only leading space.
        {
            " hello",
            "hello",
        },
        {
            "   hello",
            "hello",
        },
        // Only trailing space.
        {
            "hello ",
            "hello",
        },
        {
            "hello   ",
            "hello",
        },
        // Leading and trailing space.
        {
            " hello ",
            "hello",
        },
        {
            "   hello   ",
            "hello",
        },
    };

    for (const auto& c : test_cases) {
        std::ostringstream oss;
        // Trim leading or trailing space.
        std::regex_replace(std::ostream_iterator<char>(oss),
                           c.input.begin(), c.input.end(),
                           leading_or_trailing_space, "");
        REQUIRE(oss.str() == c.expected);
    }
}
