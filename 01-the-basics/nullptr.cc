#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// count frequency of x in p.
int count(const char *p, char x)
{
    int count = 0;
    if (p == nullptr) {
        return count;
    }
    while (*p) {
        if (*p == x) {
            ++count;
        }
        ++p;
    }
    return count;
}

TEST_CASE("[nullptr]")
{
    struct test_case
    {
        const char *input;
        char x;
        int expected;
    };

    std::vector<test_case> test_cases{
        {"Hello", 'H', 1},
        {"Hello", 'e', 1},
        {"Hello", 'l', 2},
        {"Hello", 'o', 1},
        {"Hello", 'a', 0},
        {nullptr, 'a', 0}
    };

    for (const auto& c : test_cases) {
        auto rcv = count(c.input, c.x);
        CAPTURE(c.input);
        CAPTURE(c.x);
        CAPTURE(rcv);
        CAPTURE(c.expected);
        REQUIRE(rcv == c.expected);
    }
}
