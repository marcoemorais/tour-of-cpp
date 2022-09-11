// Emit word frequency count based on input read from stdin.
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <map>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// wordcount returns word frequency count from stream.
std::map<std::string, int>
wordcount(std::istream& is)
{
    std::map<std::string, int> wc;
    std::for_each(std::istream_iterator<std::string>(is),
                  std::istream_iterator<std::string>(),
                  [&wc](const auto& s) { wc[s] += 1; });
    return wc;
}

TEST_CASE("[wordcount]")
{
    std::istringstream is{
        "one two three four two three four three four four",
    };
    auto rcv = wordcount(is);
    REQUIRE(rcv.size() == 4);
    REQUIRE(rcv["one"] == 1);
    REQUIRE(rcv["two"] == 2);
    REQUIRE(rcv["three"] == 3);
    REQUIRE(rcv["four"] == 4);
}
