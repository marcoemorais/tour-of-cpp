// Demonstrate the erase-remove idiom to remove elements from containers.
#include <algorithm>
#include <functional>
#include <iterator>
#include <list>
#include <map>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

constexpr int MAGIC{42};

TEST_CASE("[erase-remove]")
{
    // Inspired by Item 9: Choose carefully among erasing options.
    // Meyers, Scott. Effective STL. Addison-Wesley, 2001.

    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    // Set all even elements to the magic number.
    v[1] = v[3] = v[5] = v[7] = v[9] = MAGIC;

    // Calling std::remove doesn't remove elements from container,
    // it overwrites the removed elements with values that appear
    // later in the container.
    auto remove_iter = std::remove(std::begin(v), std::end(v), MAGIC);
    REQUIRE(std::size(v) == 10); // Nothing removed.
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 3);
    REQUIRE(v[2] == 5);
    REQUIRE(v[3] == 7);
    REQUIRE(v[4] == 9);
    // Everything after is undefined.

    // Calling Container::erase on the range [remove, last) removes.
    v.erase(remove_iter, std::end(v));
    REQUIRE(std::size(v) == 5); // Gone.
}

TEST_CASE("[erase-remove:idiomatic]")
{
    // Same as the erase-remove case, but idiomatically.

    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    // Set all even elements to the magic number.
    v[1] = v[3] = v[5] = v[7] = v[9] = MAGIC;

    // Combine the erase-remove in a single call.
    v.erase(std::remove(std::begin(v), std::end(v), MAGIC),
            std::end(v));
    REQUIRE(std::size(v) == 5);
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 3);
    REQUIRE(v[2] == 5);
    REQUIRE(v[3] == 7);
    REQUIRE(v[4] == 9);
}

TEST_CASE("[erase-unique:idiomatic]")
{
    // std::unique can be used in the same way as std::remove.

    std::vector<int> v = {1, 1, 1, 2, 2, 2, 3, 3, 3};

    // Combine the erase-unique in a single call.
    v.erase(std::unique(std::begin(v), std::end(v)),
            std::end(v));
    REQUIRE(std::size(v) == 3);
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 2);
    REQUIRE(v[2] == 3);
}

TEST_CASE("[erase-remove_if:idiomatic]")
{
    // std::remove_if can be used in the same way as std::remove.

    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    // Set all even elements to the magic number.
    v[1] = v[3] = v[5] = v[7] = v[9] = MAGIC;

    // Combine the erase-unique in a single call.
    v.erase(std::remove_if(std::begin(v), std::end(v),
                           std::bind(std::equal_to<>(),
                                     std::placeholders::_1,
                                     MAGIC)),
            std::end(v));
    REQUIRE(std::size(v) == 5);
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 3);
    REQUIRE(v[2] == 5);
    REQUIRE(v[3] == 7);
    REQUIRE(v[4] == 9);
}

TEST_CASE("[erase:associative]")
{
    // Don't bother with the erase-remove idiom for associative containers.
    std::map<int, int> m{
        {1, 1},
        {2, MAGIC},
        {3, 3},
        {4, MAGIC},
        {5, 5},
        {6, MAGIC},
        {7, 7},
        {8, MAGIC},
        {9, 9},
        {0, MAGIC},
    };

    // Erasing from an associative container requires iterating
    // through the container but avoiding undefined behavior
    // that results when the iterator used in the iteration
    // points to an erased element.
    for (auto first = std::begin(m), last = std::end(m); first != last; ) {
        if (first->second == MAGIC) {
            m.erase(first++); // Post-increment.
        }
        else {
            ++first;
        }
    }

    REQUIRE(std::size(m) == 5);
    REQUIRE(m.at(1) == 1);
    REQUIRE(m.at(3) == 3);
    REQUIRE(m.at(5) == 5);
    REQUIRE(m.at(7) == 7);
    REQUIRE(m.at(9) == 9);
}

TEST_CASE("[list::remove]")
{
    // Prefer list::remove member function to std::remove for
    // std::list and std::forward_list because they are more efficient.
    std::list<int> l = {1, MAGIC, 3, MAGIC, 5, MAGIC, 7, MAGIC, 9, MAGIC};

    l.remove(MAGIC);
    REQUIRE(std::size(l) == 5);
    REQUIRE(l.front() == 1);
    REQUIRE(l.back() == 9);
}
