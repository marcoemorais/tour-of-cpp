// Apply a function to every member of tuple using fold expression.

#include <functional>
#include <ostream>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

template <typename Tuple, typename Func, size_t... Indexes>
void
apply(Tuple& t, Func&& func, std::index_sequence<Indexes...>)
{
    (func(std::get<Indexes>(t)), ...);
}

template <typename Tuple, typename Func>
void
apply(Tuple& t, Func&& func)
{
    constexpr auto size = std::tuple_size<Tuple>{};
    apply(t, func, std::make_index_sequence<size>{});
}

TEST_CASE("[tuple_apply]")
{
    std::ostringstream oss;
    auto print = [&oss](const auto& v) { oss << v << ","; };

    SUBCASE("1 element tuple")
    {
        std::tuple t(42);
        apply(t, print);
        REQUIRE(oss.str() == "42,");
        oss.str("");
    }

    SUBCASE("2 element tuple")
    {
        std::tuple t(42, 3.14);
        apply(t, print);
        REQUIRE(oss.str() == "42,3.14,");
        oss.str("");
    }

    SUBCASE("3 element tuple")
    {
        std::tuple t(42, 3.14, std::string{"Hello!"});
        apply(t, print);
        REQUIRE(oss.str() == "42,3.14,Hello!,");
        oss.str("");
    }

    SUBCASE("4 element tuple, repeating types")
    {
        using namespace std::string_literals; // Required.
        auto t = make_tuple(42, 3.14, "Hello"s, "World!"s);
        apply(t, print);
        REQUIRE(oss.str() == "42,3.14,Hello,World!,");
        oss.str("");
    }
}

TEST_CASE("[pair_apply]")
{
    std::ostringstream oss;
    auto print = [&oss](const auto& v) { oss << v << ","; };

    SUBCASE("pair")
    {
        std::pair p(42, 3.14);
        apply(p, print);
        REQUIRE(oss.str() == "42,3.14,");
    }

    SUBCASE("pair, repeating types")
    {
        using namespace std::string_literals; // Required.
        auto p = std::make_pair("Hello"s, "World!"s);
        apply(p, print);
        REQUIRE(oss.str() == "Hello,World!,");
    }
}
