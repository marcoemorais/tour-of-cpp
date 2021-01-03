// Polymorphic hierarchy with pure virtual base class, container of unique_ptr to base class.
#include <cmath>
#include <memory>
#include <typeinfo>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

class Shape
{
public:
    virtual ~Shape() {} // Abstract classes require virtual destructor.

    // area returns area of shape.
    virtual double area() const = 0;

    // perimeter returns perimeter of shape.
    virtual double perimeter() const = 0;

protected:
    static constexpr double pi = 2.*std::acos(0.);
};

class Square : public Shape
{
public:
    Square() {}

    Square(double s)
        : side(s)
    {}

    double area() const override
    {
        return side*side;
    }

    double perimeter() const override
    {
        return 4*side;
    }

private:
    double side = 0.; // Default value.
};

class Circle : public Shape
{
public:
    Circle() {}

    Circle(double r)
        : radius(r)
    { }

    double area() const override
    {
        return pi*radius*radius;
    }

    double perimeter() const override
    {
        return 2.*pi*radius;
    }

private:
    double radius = 0.; // Default value.
};

double sum_area(const std::vector<std::unique_ptr<Shape>>& shapes)
{
    double sum = 0.;
    for (const auto& s : shapes) { // Use const reference to avoid transfer of ownership.
        sum += s->area();
    }
    return sum;
}

TEST_CASE("[Shape]")
{
    Square sq(2.);
    REQUIRE(sq.area() == 4.);
    REQUIRE(sq.perimeter() == 8.);

    Circle c(1.);
    REQUIRE(c.area() == M_PI);
    REQUIRE(c.perimeter() == 2.*M_PI);
}

TEST_CASE("[sum_area]")
{
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.emplace_back(std::make_unique<Square>(2.));
    shapes.emplace_back(std::make_unique<Circle>(1.));

    auto rcv = sum_area(shapes);
    REQUIRE(rcv == (shapes[0]->area() + shapes[1]->area()));
}

TEST_CASE("[dynamic_cast]")
{
    Square sq(2.);
    Shape *ps = &sq;
    Shape& rs = sq;

    REQUIRE(dynamic_cast<Square*>(ps) != nullptr);
    REQUIRE(dynamic_cast<Circle*>(ps) == nullptr);

    // dynamic_cast to reference type that fails will throw.
    REQUIRE_THROWS_AS(dynamic_cast<Circle&>(rs), std::bad_cast);
    REQUIRE_NOTHROW(dynamic_cast<Square&>(rs));
}
