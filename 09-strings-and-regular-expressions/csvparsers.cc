// All the different ways to parse a csv.
#include <algorithm>
#include <iterator>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

TEST_CASE("[getline]")
{
    std::istringstream is("one,two,three,four,five");
    char delim{','};

    // Use std::getline to parse from istream based on delimiter.
    std::vector<std::string> tokens;
    for (std::string tok; std::getline(is, tok, delim);) {
        tokens.push_back(tok);
    }

    REQUIRE(tokens ==
            std::vector<std::string>{"one","two","three","four","five"});
}

TEST_CASE("[istream_iterator]")
{
    // NOTE(mmorais): Works only with whitespace delimiter.
    std::istringstream is("one two three four five");

    std::vector<std::string> tokens;
    std::copy(std::istream_iterator<std::string>{is},
              std::istream_iterator<std::string>{},
              std::back_inserter(tokens));

    REQUIRE(tokens ==
            std::vector<std::string>{"one","two","three","four","five"});
}

TEST_CASE("[find_first_of]")
{
    // NOTE(mmorais): Works for strings only and state machine of 1 char.
    std::string s{"one,two,three,four,five"};
    char delim{','};

    std::vector<std::string> tokens;
    std::size_t start = 0, end = s.find_first_of(delim);
    while (end != std::string::npos) {
        tokens.emplace_back(s.substr(start, end-start));
        start = end + 1;
        end = s.find_first_of(delim, start);
    }
    tokens.emplace_back(s.substr(start));

    REQUIRE(tokens ==
            std::vector<std::string>{"one","two","three","four","five"});
}

TEST_CASE("[sregex_token_iterator]")
{
    // NOTE(mmorais): Works for strings only, sregex_iterator requires BidIt.
    // NOTE(mmorais): String cannot have leading or trailing delimiters.
    std::string s{"one ,  two ,  three ,  four , five"};
    std::regex delim{R"([\s,]+)"};

    std::vector<std::string> tokens;
    std::copy(std::sregex_token_iterator{std::begin(s), std::end(s),
                                         delim,
                                         -1}, // -1 return stuff btwn matches.
              std::sregex_token_iterator{},
              std::back_inserter(tokens));

    REQUIRE(tokens ==
            std::vector<std::string>{"one","two","three","four","five"});
}
