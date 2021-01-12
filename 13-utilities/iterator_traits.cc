// Implement traits-based function overload with type aliases.
#include <algorithm>
#include <forward_list>
#include <numeric>
#include <iterator>
#include <random>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// Value_type is a type alias to the value_type for a container.
template <typename Cont>
using Value_type = typename Cont::value_type;

// Iterator_type is a type alias to the iterator type for a container.
template <typename Cont>
using Iterator_type = typename Cont::iterator;

// Iterator_category is a type alias to the iterator category.
template <typename Iter>
using Iterator_category = typename std::iterator_traits<Iter>::iterator_category;

// sort_helper sorts containers with random access.
template <typename RandomAccessIter>
void sort_helper(RandomAccessIter first, RandomAccessIter last, std::random_access_iterator_tag)
{
    std::sort(first, last);
}

// sort_helper sorts containers with forward access.
template <typename ForwardIter>
void sort_helper(ForwardIter first, ForwardIter last, std::forward_iterator_tag)
{
    // Copy elements to a container with random access.
    std::vector<Value_type<ForwardIter>> v{first, last};
    std::sort(std::begin(v), std::end(v));
    // Overwrite elements with sorted copy.
    std::copy(std::begin(v), std::end(v), first);
}

// sort uses tag dispatch to select from among the overloaded sort_helper functions.
template <typename Cont>
void sort(Cont& c)
{
   using Iter = Iterator_type<Cont>; // Type of iterator.
   sort_helper(std::begin(c), std::end(c), Iterator_category<Iter>{}); // Iterator_category<> gives tag.
}

TEST_CASE("[iterator_traits]")
{
    std::default_random_engine gen{};

    // Allocate vector of 1e3 elements in random order.
    std::size_t nelems = 1'000;
    std::vector<int> nums(nelems);
    std::iota(std::begin(nums), std::end(nums), 1);
    std::shuffle(std::begin(nums), std::end(nums), gen);

    SUBCASE("std::vector")
    {
        // Confirm sort.
        auto pre = std::is_sorted(std::begin(nums), std::end(nums));
        REQUIRE(pre == false);
        sort(nums); // Uses overload based on std::random_access_iterator_tag.
        auto post = std::is_sorted(std::begin(nums), std::end(nums));
        REQUIRE(post == true);
    }

    SUBCASE("std::forward_list")
    {
        // Copy vector to std::forward_list using std::front_inserter.
        std::forward_list<int> nums_list;
        std::copy(std::begin(nums), std::end(nums),
                  std::front_inserter(nums_list));

        // Confirm sort.
        auto pre = std::is_sorted(std::begin(nums_list), std::end(nums_list));
        REQUIRE(pre == false);
        sort(nums_list); // Uses overload based on std::forward_iterator_tag.
        auto post = std::is_sorted(std::begin(nums_list), std::end(nums_list));
        REQUIRE(post == true);
    }
}
