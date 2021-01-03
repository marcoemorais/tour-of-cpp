// Read n integers from istream, c-style alloc/free functions.
#include <cstddef>
#include <sstream>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// Vector is a dynamically allocated array of numbers.
struct Vector
{
    std::size_t sz;
    double *elems;
};

// Vector_init initializes Vector with sz.
void Vector_init(Vector& v, std::size_t sz)
{
    v.elems = new double[sz];
    v.sz = sz;
}

// Vector_free frees Vector.
void Vector_free(Vector&v)
{
    delete[] v.elems;
    v.sz = 0;
}

// read_and_sum returns the sum of the values read from input.
double read_and_sum(std::istream& is, std::size_t n)
{
    Vector v;
    Vector_init(v, n);

    for (std::size_t i = 0; i != n; ++i) {
        is >> v.elems[i];
    }

    double sum = 0.;
    for (std::size_t i = 0; i != n; ++i) {
        sum += v.elems[i];
    }

    Vector_free(v);

    return sum;
}

TEST_CASE("[Vector_init]")
{
    Vector v;
    std::size_t sz{10};

    Vector_init(v, sz);
    REQUIRE(v.sz == sz);

    Vector_free(v);
}

TEST_CASE("[read_and_sum]")
{
    std::istringstream is("1 2 3 4 5");
    auto rcv = read_and_sum(is, 5);
    REQUIRE(rcv == 15);
}
