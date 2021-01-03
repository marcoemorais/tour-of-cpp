// Implement function template equivalent to std::count_if with UnaryPredicate.
#include <iterator>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// Wrap in mystd to avoid collison with std::count_if.
namespace mystd {

// count_if returns the count of elements in [first, last) that satisfy UnaryPredicate.
template <typename FwdIter, typename UnaryPredicate>
typename std::iterator_traits<FwdIter>::difference_type // Difference of iterators.
count_if(FwdIter first, FwdIter last, UnaryPredicate pred)
{
    typename std::iterator_traits<FwdIter>::difference_type count = 0;
    while (first != last) {
        if (pred(*first)) {
            ++count;
        }
        ++first;
    }
    return count;
}

// LessThan returns true when x < thresh.
template <typename T>
struct LessThan
{
    LessThan(const T& thresh)
        : thresh(thresh)
    {}

    bool operator()(const T& x)
    {
        return x < thresh;
    }

    T thresh;
};

}

TEST_CASE("[count_if]")
{
    SUBCASE("count_if using functor")
    {
        std::vector<int> v1{6,1,7,2,8,3};
        mystd::LessThan lt(5);
        auto rcv = mystd::count_if(std::begin(v1), std::end(v1), lt);
        REQUIRE(rcv == 3);
    }

    SUBCASE("count_if using lambda")
    {
        std::vector<int> v1{6,1,7,2,8,3};
        int thresh = 5;
        // Lambda syntax.
        // `&thresh` captures local variable by reference.
        // `const auto& x` takes iterator by constant reference deducing type from std::iterator_traits::value_type.
        auto rcv = mystd::count_if(std::begin(v1), std::end(v1), [&thresh](const auto& x){return x < thresh;});
        REQUIRE(rcv == 3);
    }

    SUBCASE("compare to std::count_if")
    {
        std::vector<int> v1{6,1,7,2,8,3};
        int thresh = 5;
        // Save lambda as a variable of type std::function.
        auto less_than = [&thresh](const auto& x){return x < thresh;};
        auto rcv = mystd::count_if(std::begin(v1), std::end(v1), less_than);
        auto expected = std::count_if(std::begin(v1), std::end(v1), less_than);
        REQUIRE(rcv == expected);
    }
}
