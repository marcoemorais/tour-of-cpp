// Demonstrate copy/move constructor and assignment for resource handle class.
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <utility>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// Vector demonstrates all the essential operations for a resource handle.
// Unlike POD-types, resource handles require non-default implementations.
template <typename T>
class Vector
{
public:
    // Default constructor.
    Vector() = default;

    // Ordinary constructor.
    explicit Vector(std::size_t sz)
        : elems(new T[sz])
        , sz(sz)
    {}

    // Copy constructor.
    Vector(const Vector<T>& rhs)
        : elems(new T[rhs.sz])
        , sz(rhs.sz)
    {
        std::copy(cbegin(rhs), cend(rhs), begin(*this));
    }

    // Move constructor.
    Vector(Vector<T>&& rhs)
    {
        std::swap(elems, rhs.elems);
        std::swap(sz, rhs.sz);
    }

    // Copy-assignment.
    Vector& operator=(const Vector<T>& rhs)
    {
        Vector tmp(rhs); // Create a defensive copy in case of throw.
        std::swap(elems, tmp.elems);
        std::swap(sz, tmp.sz);
        return *this;
    }

    // Move-assignment.
    Vector& operator=(Vector<T>&& rhs)
    {
        std::swap(elems, rhs.elems);
        std::swap(sz, rhs.sz);
        return *this;
    }

    // Destructor.
    ~Vector()
    {
        delete []elems;
        sz = 0;
    }

    // Non-const access to elements of Vector.
    T& operator[](std::size_t i)
    {
        return elems[i];
    }

    // Const access to elements of Vector.
    const T& operator[](std::size_t i) const
    {
        return elems[i];
    }

    // Size returns number of elements.
    std::size_t size() const
    {
        return sz;
    }

private:
    // Default initial value is empty Vector.
    T *elems = nullptr;
    std::size_t sz = 0;
};

// begin satisfies requirements for range-based for loop.
template <typename T>
T* begin(Vector<T>& v)
{
    return v.size() ? &v[0] : nullptr;
}

// end satisfies requirements for range-based for loop.
template <typename T>
T* end(Vector<T>& v)
{
    return v.size() ? &v[0]+v.size() : nullptr;
}

// cbegin satisfies requirements for range-based for loop.
template <typename T>
const T* cbegin(const Vector<T>& v)
{
    return v.size() ? &v[0] : nullptr;
}

// cend satisfies requirements for range-based for loop.
template <typename T>
const T* cend(const Vector<T>& v)
{
    return v.size() ? &v[0]+v.size() : nullptr;
}

TEST_CASE("[Vector]")
{
    Vector<int> v1;
    Vector<int> v2(5);
    for (std::size_t i = 0; i != v2.size(); ++i) {
        v2[i] = int(i);
    }

    SUBCASE("Default constructor")
    {
        REQUIRE(v1.size() == 0);
    }

    SUBCASE("Ordinary constructor")
    {
        for (std::size_t i = 0; i != v2.size(); ++i) {
            REQUIRE(v2[i] == int(i));
        }
    }

    SUBCASE("Range-based for loop, non-const reference")
    {
        std::size_t i = 0;

        // Non-const reference returned from begin/end.
        for (auto& x : v2) {
            REQUIRE(v2[i] == x);
            ++i;
        }
    }

    SUBCASE("Range-based for loop, const reference")
    {
       std::size_t i = 0;

        // Const reference returned from cbegin/cend.
        for (const auto& x : v2) {
            REQUIRE(v2[i] == x);
            ++i;
        }
    }

    SUBCASE("Copy constructor")
    {
        Vector<int> v3(v2);

        for (std::size_t i = 0; i != v3.size(); ++i) {
            REQUIRE(v3[i] == int(i));
        }
    }

    SUBCASE("Move constructor")
    {
        Vector<int> v3(std::move(v2));

        for (std::size_t i = 0; i != v3.size(); ++i) {
            REQUIRE(v3[i] == int(i));
        }
        REQUIRE(v2.size() == 0);
    }

    SUBCASE("Copy assignment")
    {
        Vector<int> v3 = v2;

        for (std::size_t i = 0; i != v3.size(); ++i) {
            REQUIRE(v3[i] == int(i));
        }
    }

    SUBCASE("Move assignment")
    {
        Vector<int> v3 = std::move(v2);

        for (std::size_t i = 0; i != v3.size(); ++i) {
            REQUIRE(v3[i] == int(i));
        }
        REQUIRE(v2.size() == 0);
    }
}
