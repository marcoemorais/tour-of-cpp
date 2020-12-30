#include <algorithm>
#include <cstddef>
#include <initializer_list>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

template <typename T>
class Vector
{
public:
    explicit Vector(std::size_t sz)
        : elems(new T[sz])
        , sz(sz)
    { }

    // Intentionally not a const reference, but a copy.
    Vector(std::initializer_list<T> lst)
        : elems(new T[lst.size()])
        , sz(lst.size())
    {
        std::copy(std::begin(lst), std::end(lst), elems);
    }

    ~Vector()
    {
        delete []elems;
    }

    T& operator[](std::size_t i)
    {
        return elems[i];
    }

    std::size_t size() const
    {
        return sz;
    }

private:
    T *elems;
    std::size_t sz;
};

TEST_CASE("[Vector]")
{
    // Initialize Vector with sz.
    {
        std::size_t n{10};
        Vector<int> v(n);

        REQUIRE(v.size() == n);
    }

    // Initialize Vector with list of numbers.
    {
        Vector<double> v{0., 0.25, 0.5, 0.75, 1.};

        REQUIRE(v.size() == 5);
        REQUIRE(v[0] == 0.);
        REQUIRE(v[1] == 0.25);
        REQUIRE(v[2] == 0.5);
        REQUIRE(v[3] == 0.75);
        REQUIRE(v[4] == 1.);
    }
}
