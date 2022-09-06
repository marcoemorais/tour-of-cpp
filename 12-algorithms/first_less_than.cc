// first_less_than complements lower_bound and upper_bound.
#include <algorithm>
#include <iterator>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// first_less_than returns iterator to first in [first, last) < v.
template <typename FwdIter, typename Value>
FwdIter first_less_than(FwdIter first, FwdIter last, const Value& v)
{
    auto it = std::lower_bound(first, last, v);
    return it == first ? last : --it;
}

TEST_CASE("[first_less_than]")
{
    std::vector<int> v = {2, 4, 6, 8};

    // Search for value not less than any value in v.
    {
        auto it = first_less_than(begin(v), end(v), 2);
        REQUIRE(it == end(v));
    }

    // Search for value greater than first value in v.
    {
        auto it = first_less_than(begin(v), end(v), 4);
        REQUIRE(it != end(v));
        REQUIRE(*it == 2);
    }

    // Search for value greater than last value in v.
    {
        auto it = first_less_than(begin(v), end(v), 99);
        REQUIRE(it != end(v));
        REQUIRE(*it == 8);
    }
}
