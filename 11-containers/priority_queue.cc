// Demonstrate std::priority_queue using lambda functions for ordering.
#include <functional>
#include <iterator>
#include <queue>
#include <utility>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

TEST_CASE("[priority_queue:max_heap]")
{
    // Heap contains a pair of ints.
    using HeapEntry = std::pair<int, int>;

    // Use a lambda function to define heap ordering.
    auto HeapEntryLess  = [](const HeapEntry& h1, const HeapEntry& h2) {
        return h1.first == h2.first ?
            h1.second < h2.second :
            h1.first < h2.first;
    };

    // Data to insert to queue.
    std::vector<HeapEntry> pairs{
        {1, 1}, {1, 2}, {1, 3},
        {2, 1}, {2, 2}, {2, 3},
        {3, 1}, {3, 2}, {3, 3},
    };

    // Max heap ordered using HeapEntryLess e.g. equivalent to less<T>.
    std::priority_queue<HeapEntry,
                        std::vector<HeapEntry>,
                        decltype(HeapEntryLess)>
        max_heap(std::begin(pairs), std::end(pairs), HeapEntryLess);

    REQUIRE(std::size(max_heap) == std::size(pairs));

    // Check top of heap.
    REQUIRE(max_heap.top() == HeapEntry{3, 3});

    // Pop from heap and recheck top.
    max_heap.pop();
    REQUIRE(max_heap.top() == HeapEntry{3, 2});

    // Add entry that does not replace top.
    max_heap.emplace(2, 4);
    REQUIRE(max_heap.top() == HeapEntry{3, 2});

    // Add entry that replaces top.
    max_heap.emplace(3, 4);
    REQUIRE(max_heap.top() == HeapEntry{3, 4});
}

TEST_CASE("[priority_queue:min_heap]")
{
    // Heap contains a pair of ints.
    using HeapEntry = std::pair<int, int>;

    // Use a lambda function to define heap ordering.
    auto HeapEntryGreater  = [](const HeapEntry& h1, const HeapEntry& h2) {
        return h1.first == h2.first ?
            h1.second > h2.second :
            h1.first > h2.first;
    };

    // Data to insert to queue.
    std::vector<HeapEntry> pairs{
        {1, 1}, {1, 2}, {1, 3},
        {2, 1}, {2, 2}, {2, 3},
        {3, 1}, {3, 2}, {3, 3},
    };

    // Min heap ordered using HeapEntryGreater e.g. equivalent to greater<T>.
    std::priority_queue<HeapEntry,
                        std::vector<HeapEntry>,
                        decltype(HeapEntryGreater)>
        min_heap(std::begin(pairs), std::end(pairs), HeapEntryGreater);

    REQUIRE(std::size(min_heap) == std::size(pairs));

    // Check top of heap.
    REQUIRE(min_heap.top() == HeapEntry{1, 1});

    // Pop from heap and recheck top.
    min_heap.pop();
    REQUIRE(min_heap.top() == HeapEntry{1, 2});

    // Add entry that does not replace top.
    min_heap.emplace(2, 4);
    REQUIRE(min_heap.top() == HeapEntry{1, 2});

    // Add entry that replaces top.
    min_heap.emplace(1, 0);
    REQUIRE(min_heap.top() == HeapEntry{1, 0});
}
