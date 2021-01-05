// Implement template function findall that demonstrates use of type alias.
#include <set>
#include <string>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// Iterator is a type alias to the iterator type for a container.
template <typename Cont>
using Iterator = typename Cont::iterator;

// findall returns iterators to all matching values in a container.
template <typename Cont, typename Value>
std::vector<Iterator<Cont>> findall(Cont& c, const Value& v)
{
    std::vector<Iterator<Cont>> result;
    for (auto iter = std::begin(c); iter != std::end(c); ++iter) {
        if (*iter == v) {
            result.push_back(iter);
        }
    }
    return result;
}

TEST_CASE("[findall]")
{
    SUBCASE("std::string")
    {
        //             0123456789012345678901
        std::string s("Mary had a little lamb");

        std::vector<std::string::iterator> expected{
            std::begin(s)+4,
            std::begin(s)+8,
            std::begin(s)+10,
            std::begin(s)+17,
        };

        auto rcv = findall(s, ' ');
        REQUIRE(rcv.size() == expected.size());
        REQUIRE(rcv == expected);
    }

    SUBCASE("std::multiset")
    {
        std::multiset<int> s{0,2,4,6,8,2,12,14,16,2,20};

        int v = 2;
        auto [first, last] = s.equal_range(v);
        std::vector<std::multiset<int>::iterator> expected;
        while (first != last) {
            expected.push_back(first);
            ++first;
        }

        auto rcv = findall(s, v);
        REQUIRE(rcv.size() == expected.size());
        REQUIRE(rcv == expected);
    }
}
