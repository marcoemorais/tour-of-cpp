// Demonstrate use of std::inserter for adding elements to container.
#include <algorithm>
#include <istream>
#include <iterator>
#include <list>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

using namespace std::string_literals; // Required.

struct entry
{
    std::string name;
    int value;
};

// operator>> deserializes entry from std::istream.
std::istream& operator>>(std::istream& is, entry& e)
{
    is >> e.name;
    is >> e.value;
    return is;
}

// operator< provides default sort order for ordered containers.
bool operator<(const entry& e1, const entry& e2)
{
    return e1.name < e2.name || e1.value < e2.value;
}

TEST_CASE("[inserter]")
{

    std::istringstream is(
        "Alice 1\n"
        "Bob 2\n"
        "Chuck 3\n"
        "Denise 4\n"
    );

    SUBCASE("std::back_inserter")
    {
        // Deserialize from std::istringstream to objects of type entry.
        // Call std::vector::push_back on each such object.
        std::vector<entry> v;
        std::copy(std::istream_iterator<entry>(is),
                  std::istream_iterator<entry>(),
                  std::back_inserter(v));
        REQUIRE(v.size() == 4);
        REQUIRE(v[0].name == "Alice"s);
        REQUIRE(v[0].value == 1);
        REQUIRE(v[3].name == "Denise"s);
        REQUIRE(v[3].value == 4);
    }

    SUBCASE("std::front_inserter")
    {
        // Deserialize from std::istringstream to objects of type entry.
        // Call std::list::push_front on each such object.
        std::list<entry> l;
        std::copy(std::istream_iterator<entry>(is),
                  std::istream_iterator<entry>(),
                  std::front_inserter(l));
        // Reverse order of std::back_inserter.
        REQUIRE(l.size() == 4);
        REQUIRE(l.front().name == "Denise"s);
        REQUIRE(l.front().value == 4);
        REQUIRE(l.back().name == "Alice"s);
        REQUIRE(l.back().value == 1);
    }

    SUBCASE("std::inserter")
    {
        // Deserialize from std::istringstream to objects of type entry.
        // Call std::list::push_front on each such object.
        std::set<entry> s;
        std::copy(std::istream_iterator<entry>(is),
                  std::istream_iterator<entry>(),
                  std::inserter(s, std::end(s))); // NOTE: Use std::end as pos.
        REQUIRE(s.size() == 4);
        REQUIRE(s.count({"Alice"s, 1}) == 1);
        REQUIRE(s.count({"Bob"s, 2}) == 1);
        REQUIRE(s.count({"Chuck"s, 3}) == 1);
        REQUIRE(s.count({"Denise"s, 4}) == 1);
    }
}
