#include <cstddef>
#include <cmath>
#include <sstream>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// Vector mimics an STL container.
class Vector
{
public:
    Vector(std::size_t sz)
        : elems(new double[sz])
        , sz(sz)
    { }

    ~Vector()
    {
        delete[] elems;
        sz = 0;
    }

    double& operator[](std::size_t i)
    {
        return elems[i];
    }

    std::size_t size() const
    {
        return sz;
    }

private:
    double *elems;
    std::size_t sz;
};

// read_and_sum returns the sum of the values read from input.
double read_and_sum(std::istream& is, std::size_t n)
{
    Vector v{n};

    for (std::size_t i = 0; i != n; ++i) {
        is >> v[i];
    }

    double sum = 0.;
    for (std::size_t i = 0; i != n; ++i) {
        sum += v[i];
    }

    return sum;
}

TEST_CASE("[Vector]")
{
    std::size_t n{10};
    Vector v(n);

    REQUIRE(v.size() == n);

    constexpr double pi = 2.*std::acos(0.);
    v[n/2] = pi;
    CAPTURE(v[n/2]);
    REQUIRE(v[n/2] == pi);
}

TEST_CASE("[read_and_sum]")
{
    std::istringstream is("1 10 100 1000 10000");
    auto rcv = read_and_sum(is, 5);
    REQUIRE(rcv == doctest::Approx(11111.));
}
