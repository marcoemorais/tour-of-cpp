// Implement function template equivalent to std::for_each with UnaryFunction.
#include <algorithm>
#include <cstddef>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// Wrap in mystd to avoid collison with std::for_each.
namespace mystd {

// for_each calls UnaryFunction on each element in [first, last).
// UnaryFunction will be implicitly moved.
template <typename FwdIter, typename UnaryFunction>
UnaryFunction
for_each(FwdIter first, FwdIter last, UnaryFunction f)
{
    while (first != last) {
        f(*first);
        ++first;
    }
    return f;
}

// Avg computes the cumulative moving average (CMA) of the input.
template <typename T>
struct Avg
{
    void operator()(const T& x)
    {
        mu = (x + n*mu)/(n+1);
        n += 1;
    }

    std::size_t n = 0;
    double mu = 0.;
};

}

TEST_CASE("[for_each]")
{
    SUBCASE("for_each using functor")
    {
        std::vector<int> v1{1,2,3,4,5};
        mystd::Avg<int> avg;
        avg = mystd::for_each(std::begin(v1), std::end(v1), avg); // Implicit std::move.
        REQUIRE(avg.mu == 3.0);
    }

    SUBCASE("for_each using lambda")
    {
        std::vector<int> v1{1,2,3,4,5};
        // For lambda, the state is maintained via the captured reference.
        int maxv = 0.;
        auto maxf = [&maxv](const auto& x){maxv = std::max(x, maxv);};
        mystd::for_each(std::begin(v1), std::end(v1), maxf);
        REQUIRE(maxv == 5);
    }

    SUBCASE("compare to std::for_each")
    {
        std::vector<int> v1{1,2,3,4,5};
        mystd::Avg<int> avg;
        avg = mystd::for_each(std::begin(v1), std::end(v1), avg); // Implicit std::move.
        mystd::Avg<int> expected;
        expected = std::for_each(std::begin(v1), std::end(v1), expected);
        REQUIRE(avg.mu == expected.mu);
    }
}
