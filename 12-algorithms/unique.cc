// Implement function template equivalent to std::unique for removing adjacent duplicate values.
#include <vector>
#include <iostream>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// Wrap in mystd to avoid collison with std::unique.
namespace mystd {

// unique removes adjacent duplicate values and returns new end of range without duplicates.
template <typename FwdIter>
FwdIter unique(FwdIter first, FwdIter last)
{
    FwdIter end = first+1;
    while (end != last) {
        if (*first != *end) {
            ++first;
            if (*first != *end) {
                *first = *end; // Overwrite duplicate value.
            }
        }
        ++end;
    }
    ++first; // One past newend.
    return first;
}

}

TEST_CASE("[unique]")
{
    struct test_case
    {
        std::vector<int> input;
        std::vector<int> expected;
    };

    std::vector<test_case> test_cases{
        // No duplicates.
        {
            {1,2,3},
            {1,2,3},
        },
        // First element appears twice.
        {
            {1,1,2,3},
            {1,2,3},
        },
        // Middle element appears twice.
        {
            {1,2,2,3},
            {1,2,3},
        },
        // Last element appears twice.
        {
            {1,2,3,3},
            {1,2,3},
        },
        // All elements appear 3 times.
        {
            {1,1,1,2,2,2,3,3,3},
            {1,2,3},
        },
    };

    for (auto& c : test_cases) {
        auto newend = mystd::unique(std::begin(c.input), std::end(c.input));
        std::vector<int> rcv(std::begin(c.input), newend);
        REQUIRE(rcv.size() == c.expected.size());
        REQUIRE(rcv == c.expected);
    }
}
