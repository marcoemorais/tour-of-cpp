#include <algorithm>
#include <cassert>
#include <cmath>
#include <string>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// base_string returns the number n as a string in an arbitrary base.
std::string
base_string(int n, const int base=10)
{
    assert(n > 0); // n is positive.
    int nbits = std::ceil(std::log(n)/std::log(base));
    std::string basenstr(nbits, '0');
    for (auto digit = 0; digit != nbits; ++digit) {
        basenstr[digit] = '0' + (n % base);
        n = n / base;
    }
    std::reverse(std::begin(basenstr), std::end(basenstr));
    return basenstr;
}

TEST_CASE("[base]")
{
    struct test_case
    {
        int n;
        int base;
        std::string expected;
    };

    std::vector<test_case> test_cases{
        {
            624, 10, "624"
        },
        {
            624, 16, "270"
        },
        {
            624, 8, "1160"
        },
        {
            624, 2, "1001110000"
        },
    };

    for (const auto& c : test_cases) {
        auto rcv = base_string(c.n, c.base);
        CAPTURE(c.n);
        CAPTURE(c.base);
        REQUIRE(rcv == c.expected);
    }
}
