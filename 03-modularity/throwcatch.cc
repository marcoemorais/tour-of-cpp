// Demonstrate cpp convention of throw-by-value and catch by (const) reference.
#include <iostream>
#include <stdexcept>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

void throws()
{
    throw std::out_of_range("always throws"); // Throw by value.
}

void catches()
{
    try {
        throws();
    }
    catch(std::out_of_range& err) { // Catch by reference.
        std::cerr << "caught: " << err.what() << "\n";
    }
}

TEST_CASE("[throwcatch]")
{
    REQUIRE_THROWS_AS(throws(), std::out_of_range);
    REQUIRE_NOTHROW(catches());
}
