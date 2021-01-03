// Demonstrate copy/move constructor and assignment for POD-type class.
#include <algorithm>
#include <cstddef>
#include <istream>
#include <ostream>
#include <sstream>
#include <utility>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// Mat3x3 demonstrates all essential operations for a POD-type.
// Many of these operations could be implicitly compiler generated,
// but aren't in order to demonstrate semantics.
class Mat3x3
{
public:
    // Default constructor, compiler generated.
    Mat3x3() = default;

    // Ordinary constructor.
    explicit Mat3x3(double m0)
    {
        std::fill(&m[i0], &m[iN], m0);
    }

    // Copy constructor.
    Mat3x3(const Mat3x3& rhs)
    {
        std::copy(&rhs.m[i0], &rhs.m[iN], &m[i0]);
    }

    // Move constructor.
    Mat3x3(Mat3x3&& rhs)
    {
        std::swap(m, rhs.m); // Move implemented through std::swap.
    }

    // Copy-assignment.
    Mat3x3& operator=(const Mat3x3& rhs)
    {
        std::copy(&rhs.m[i0], &rhs.m[iN], &m[i0]);
        return *this;
    }

    // Move-assignment.
    Mat3x3& operator=(Mat3x3&& rhs)
    {
        std::swap(m, rhs.m); // Move implemented through std::swap.
        return *this;
    }

    // Destructor, compiler generated.
    ~Mat3x3() = default;

    // Non-const access to elements of matrix through double index.
    double& operator()(std::size_t i, std::size_t j)
    {
        return m[i*D+j];
    }

    // Const access to elements of matrix through double index.
    const double& operator()(std::size_t i, std::size_t j) const
    {
        return m[i*D+j];
    }

    // Overloaded output operator.
    friend std::ostream& operator<<(std::ostream& os, const Mat3x3& m);

    // Overloaded input operator.
    friend std::istream& operator>>(std::istream& is, Mat3x3& m);

private:
    double m[9] = {0.};

    // Index of first and last element in matrix.
    static constexpr std::size_t i0 = 0;
    static constexpr std::size_t iN = 9;

    // Index of dimension of matrix.
    static constexpr std::size_t D = 3;
};

// Overloaded output operator.
std::ostream& operator<<(std::ostream& os, const Mat3x3& m)
{
    os << "[";
    for (std::size_t i = 0; i != 3; ++i) {
        os << "[";
        for (std::size_t j = 0; j != 3; ++j) {
            os << m(i,j) << (j != 2 ? "," : "");
        }
        os << "]" << (i !=2 ? "," : "");
    }
    os << "]";
    return os;
}

// Overloaded input operator.
std::istream& operator>>(std::istream& is, Mat3x3& m)
{
    char c;
    is>>c; // Discard: [
    for (std::size_t i = 0; i != 3; ++i) {
        is>>c; // Discard: [
        for (std::size_t j = 0; j != 3; ++j) {
            is>>m(i,j);
            if (j != 2) {
                is>>c; // Discard: ,
            }
        }
        is>>c; // Discard: ]
        if (i != 2) {
            is>>c; // Discard: ,
        }
    }
    return is;
}

TEST_CASE("[Mat3x3]")
{
    Mat3x3 m1;
    Mat3x3 m2(5.);

    SUBCASE("Default constructor")
    {
        for (std::size_t i = 0; i != 3; ++i) {
            for (std::size_t j = 0; j != 3; ++j) {
                REQUIRE(m1(i,j) == 0.);
            }
        }
    }

    SUBCASE("Ordinary constructor")
    {
        for (std::size_t i = 0; i != 3; ++i) {
            for (std::size_t j = 0; j != 3; ++j) {
                REQUIRE(m2(i,j) == 5.);
            }
        }
    }

    SUBCASE("Copy constructor")
    {
        Mat3x3 m3(m2);

        for (std::size_t i = 0; i != 3; ++i) {
            for (std::size_t j = 0; j != 3; ++j) {
                REQUIRE(m2(i,j) == 5.);
                REQUIRE(m3(i,j) == 5.);
            }
        }
    }

    SUBCASE("Move constructor")
    {
        Mat3x3 m3(std::move(m2));

        for (std::size_t i = 0; i != 3; ++i) {
            for (std::size_t j = 0; j != 3; ++j) {
                REQUIRE(m2(i,j) == 0.);
                REQUIRE(m3(i,j) == 5.);
            }
        }
    }

    SUBCASE("Copy assignment")
    {
        Mat3x3 m3 = m2;

        for (std::size_t i = 0; i != 3; ++i) {
            for (std::size_t j = 0; j != 3; ++j) {
                REQUIRE(m2(i,j) == 5.);
                REQUIRE(m3(i,j) == 5.);
            }
        }
    }

    SUBCASE("Move assignment")
    {
        Mat3x3 m3 = std::move(m2);

        for (std::size_t i = 0; i != 3; ++i) {
            for (std::size_t j = 0; j != 3; ++j) {
                REQUIRE(m2(i,j) == 0.);
                REQUIRE(m3(i,j) == 5.);
            }
        }
    }
}

TEST_CASE("[Mat3x3::operator<<]")
{
    Mat3x3 m;

    for (std::size_t i = 0; i != 3; ++i) {
        for (std::size_t j = 0; j != 3; ++j) {
            m(i,j) = i*3+j;
        }
    }

    std::ostringstream oss;
    oss << m;
    REQUIRE(oss.str() == "[[0,1,2],[3,4,5],[6,7,8]]");
}

TEST_CASE("[Mat3x3::operator>>]")
{
    Mat3x3 m(5.);

    std::istringstream iss("[[0,1,2],[3,4,5],[6,7,8]]");
    iss >> m;

    for (std::size_t i = 0; i != 3; ++i) {
        for (std::size_t j = 0; j != 3; ++j) {
            REQUIRE(m(i,j) == i*3+j);
        }
    }
}
