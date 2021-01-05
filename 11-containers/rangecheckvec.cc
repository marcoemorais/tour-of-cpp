// Demonstrate using composition to obtain range-checked std::vector.
#include <cstddef>
#include <numeric>
#include <stdexcept>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

template <typename T>
class RangeCheckedVec : public std::vector<T>
{
public:
    using std::vector<T>::vector; // Includes the entire interface of std::vector.

    // Replace definition of operator[] with range-checked equivalent.
    T& operator[](std::size_t i)
    {
        return std::vector<T>::at(i);
    }

    const T& operator[](std::size_t i) const
    {
        return std::vector<T>::at(i);
    }
};

TEST_CASE("[rangecheckvec]")
{
    int n = 10;
    RangeCheckedVec<int> v(n);
    std::iota(std::begin(v), std::end(v), n);
    REQUIRE(v.size() == n);

    // Access by index [0, n) using operator[].
    for (auto i = 0; i != n; ++i) {
        REQUIRE_NOTHROW(v[i]);
    }

    // Access out of range using operator[].
    REQUIRE_THROWS_AS(v[n], std::out_of_range);
}
