// Demonstrate heap functions in std::algorithms.
#include <algorithm>
#include <iterator>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

TEST_CASE("[max_heap]")
{
    std::vector<int> max_heap = {1, 2, 3, 4, 5};

    // Create a heap from vector.
    std::make_heap(begin(max_heap), end(max_heap)); // Uses less<T>.
    REQUIRE(max_heap.front() == 5);

    // Pop moves element to end of heap, but does not remove.
    std::pop_heap(begin(max_heap), end(max_heap));
    REQUIRE(max_heap.front() == 4);
    REQUIRE(max_heap.back() == 5);
    REQUIRE(max_heap.size() == 5);

    // Remove from heap.
    max_heap.pop_back();
    REQUIRE(max_heap.size() == 4);

    // Pop again.
    std::pop_heap(begin(max_heap), end(max_heap));
    REQUIRE(max_heap.front() == 3);
    REQUIRE(max_heap.back() == 4);

    // Remove from heap.
    max_heap.pop_back();
    REQUIRE(max_heap.size() == 3);

    // Push element onto heap.
    max_heap.push_back(-99);
    std::push_heap(begin(max_heap), end(max_heap));
    REQUIRE(max_heap.front() == 3); // Top of heap not changed.
    REQUIRE(max_heap.size() == 4);

    // Push element onto heap, replaces top.
    max_heap.push_back(99);
    std::push_heap(begin(max_heap), end(max_heap));
    REQUIRE(max_heap.front() == 99);
    REQUIRE(max_heap.size() == 5);
}

TEST_CASE("[min_heap]")
{
    std::vector<int> min_heap = {5, 4, 3, 2, 1};

    auto comp = std::greater<int>();

    // Create a heap from vector.
    std::make_heap(begin(min_heap), end(min_heap), comp); // Uses greater<T>.
    REQUIRE(min_heap.front() == 1);

    // Pop moves element to end of heap, but does not remove.
    std::pop_heap(begin(min_heap), end(min_heap), comp);
    REQUIRE(min_heap.front() == 2);
    REQUIRE(min_heap.back() == 1);
    REQUIRE(min_heap.size() == 5);

    // Remove from heap.
    min_heap.pop_back();
    REQUIRE(min_heap.size() == 4);

    // Pop again.
    std::pop_heap(begin(min_heap), end(min_heap), comp);
    REQUIRE(min_heap.front() == 3);
    REQUIRE(min_heap.back() == 2);

    // Remove from heap.
    min_heap.pop_back();
    REQUIRE(min_heap.size() == 3);

    // Push element onto heap.
    min_heap.push_back(99);
    std::push_heap(begin(min_heap), end(min_heap), comp);
    REQUIRE(min_heap.front() == 3); // Top of heap not changed.
    REQUIRE(min_heap.size() == 4);

    // Push element onto heap, replaces top.
    min_heap.push_back(-99);
    std::push_heap(begin(min_heap), end(min_heap), comp);
    REQUIRE(min_heap.front() == -99);
    REQUIRE(min_heap.size() == 5);
}

TEST_CASE("[sort_heap]")
{
    std::vector<int> max_heap = {1, 2, 3, 4, 5};

    // Create a heap from vector.
    std::make_heap(begin(max_heap), end(max_heap)); // Uses less<T>.

    // vector satisfies heap property, but is not sorted.
    REQUIRE(std::is_heap(begin(max_heap), end(max_heap)) == true);
    REQUIRE(std::is_sorted(begin(max_heap), end(max_heap)) == false);

    // Sort the heap.
    std::sort_heap(begin(max_heap), end(max_heap));

    // vector no longer satisfies heap property, but is sorted.
    REQUIRE(std::is_heap(begin(max_heap), end(max_heap)) == false);
    REQUIRE(std::is_sorted(begin(max_heap), end(max_heap)) == true);
}
