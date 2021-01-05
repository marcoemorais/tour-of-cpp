// Demonstrate use of custom hash functions with containers.
#include <cstddef>
#include <functional>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>
#include <unordered_map>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

using namespace std::string_literals; // Required.

// hash_value hashes any T supported by std::hash.
template <typename T>
std::size_t hash_value(const T& v)
{
    return std::hash<T>()(v);
}

// std::hash<std::tuple> is a variadic template based on tuple types.
template <class... TupleArgs>
struct std::hash<std::tuple<TupleArgs...>>
{
public:
    std::size_t operator()(const std::tuple<TupleArgs...>& t) const
    {
        // std::make_index_sequence returns tuple indices {0, 1, ..., sizeof(TupleArgs)-1}.
        return hash_combine(t, std::make_index_sequence<sizeof...(TupleArgs)>());
    }

private:
    // hash_combine is used to incrementally build a hash value.
    // Copy-paste of bost::hash_combine.
    template <typename Tuple, std::size_t... ids>
    std::size_t hash_combine(const Tuple& t, std::index_sequence<ids...> const&) const
    {
        std::size_t seed = 0;
        // Get the hash_value for each component of tuple by index.
        for (const auto& hv : {hash_value(std::get<ids>(t))...}) {
            seed ^= hv + 0x9e3779b9 + (seed<<6) + (seed>>2);
        }
        return seed;
    }
};

TEST_CASE("[customhash]")
{
    SUBCASE("std::tuple")
    {
        using Tuple3 = std::tuple<int, int, int>;
        Tuple3 xyz1{1, 1, 1};
        Tuple3 xyz2{1, 1, 1};

        // Different objects, but same hash.
        REQUIRE(std::hash<Tuple3>()(xyz1) == std::hash<Tuple3>()(xyz2));

        // Different values and different hash.
        Tuple3 xyz3{2, 3, 4};
        REQUIRE(std::hash<Tuple3>()(xyz1) != std::hash<Tuple3>()(xyz3));
    }

    SUBCASE("std::unordered_map")
    {
        using XYZ = std::tuple<double, double, double>;
        std::unordered_map<XYZ, std::string> m1{
            {{0.,0.,0.}, "origin"s},
            {{1.,1.,1.}, "ones"s},
            {{-1.,-1.,-1.}, "negones"s}
        };

        // Expected to find.
        auto f1 = m1.find({0.,0.,0.});
        REQUIRE(f1 != std::end(m1));
        REQUIRE((*f1).second == "origin"s);

        // Expected to not find.
        auto f2 = m1.find({2.,4.,6.});
        REQUIRE(f2 == std::end(m1));
    }
}
