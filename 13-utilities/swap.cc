// Demonstrate exception safe swap implemented using std::move.
#include <algorithm>
#include <cstddef>
#include <numeric>
#include <utility>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// swap lhs and rhs using exception safe semantics.
template <typename T>
void swap(T& lhs, T& rhs)
{
    // Construct temporary object by moving lhs into temp.
    T temp{std::move(lhs)};
    lhs = std::move(rhs);
    rhs = std::move(temp);
}

TEST_CASE("[swap]")
{
    std::size_t N = 10;
    // v1 holds values {1, 2, ..., N}.
    std::vector<int> v1(N);
    std::iota(std::begin(v1), std::end(v1), 1);
    // v2 holds values {N, N-1, ..., 1}.
    std::vector<int> v2(N);
    std::reverse_copy(std::begin(v1), std::end(v1), std::begin(v2));

    REQUIRE(v1[0] == 1);
    REQUIRE(v1[N-1] == N);
    REQUIRE(v2[0] == N);
    REQUIRE(v2[N-1] == 1);

    swap(v1, v2); // Swap v1 and v2.

    REQUIRE(v1[0] == N);
    REQUIRE(v1[N-1] == 1);
    REQUIRE(v2[0] == 1);
    REQUIRE(v2[N-1] == N);
}
