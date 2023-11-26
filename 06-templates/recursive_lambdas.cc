// Demonstrate methods for creating recursive lambda functions.
#include <functional>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

TEST_CASE("[recursive_lambda:auto]")
{
    // factorial is a lambda with a generic lambda parameter.
    // Every lambda invocation must also pass the lambda parameter.
    auto factorial = [](const int n, auto&& factorial) {
        if (n < 1) {
            return 1;
        }
        return n * factorial(n - 1, factorial);
    };

    REQUIRE(factorial(5, factorial) == 120);
    REQUIRE(factorial(4, factorial) == 24);
    REQUIRE(factorial(3, factorial) == 6);
    REQUIRE(factorial(2, factorial) == 2);
    REQUIRE(factorial(1, factorial) == 1);
    REQUIRE(factorial(0, factorial) == 1);
}

TEST_CASE("[recursive_lambda:function]")
{
    // Factorial is type of std::function, so we no
    // longer have to pass the lambda with each invocation.
    // The lambda captures a reference to itself.
    using Factorial = std::function<int(const int n)>;
    Factorial factorial = [&factorial](const int n) {
        if (n < 1) {
            return 1;
        }
        return n * factorial(n - 1);
    };

    REQUIRE(factorial(5) == 120);
    REQUIRE(factorial(4) == 24);
    REQUIRE(factorial(3) == 6);
    REQUIRE(factorial(2) == 2);
    REQUIRE(factorial(1) == 1);
    REQUIRE(factorial(0) == 1);
}
