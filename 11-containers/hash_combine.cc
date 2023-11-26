// Demonstrate combining hash functions.
#include <cstddef>
#include <functional>
#include <iterator>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

template<class>
constexpr bool dependent_false = false;

template <typename T>
inline void _hash_combine(std::size_t& seed, const T& val)
{
    // Magic numbers in boost::hash_combine assume sizeof(size_t) == 4
    // Extend support to sizeof(size_t) == 8 based on
    // https://github.com/HowardHinnant/hash_append/issues/7
    if constexpr (sizeof(std::size_t) == 4) {
        seed ^= std::hash<T>()(val) + 0x9e3779b9 + (seed<<6) + (seed>>2);
    }
    else if constexpr (sizeof(std::size_t) == 8) {
        seed ^= std::hash<T>()(val) + 0x9e3779b97f4a7c15LLU + (seed<<12) +
            (seed>>4);
    }
    else {
        static_assert(dependent_false<T>, "hash_combine not supported");
    }
}

template <typename... Types>
std::size_t hash_combine(const Types&... args)
{
    // Copy-paste of
    // https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p0814r2.pdf
    std::size_t seed = 0;
    (_hash_combine(seed, args), ...); // Fold expression with seed over args.
    return seed;
}

template <class, class Enable = void>
struct is_iterator : std::false_type {};

template <typename T>
struct is_iterator<T, typename std::enable_if<std::is_pointer<typename
     std::iterator_traits<T>::pointer>::value>::type> : std::true_type {};

// Overload when is_iterator<T> is true.
template <typename InputIterator,
          std::enable_if_t<is_iterator<std::decay_t<InputIterator>>{}>* = nullptr>
std::size_t hash_combine(InputIterator first, InputIterator last)
{
    std::size_t seed = 0;
    while (first != last) {
        _hash_combine(seed, *first++);
    }
    return seed;
}

TEST_CASE("[hash_combine]")
{
    SUBCASE("noncommutative")
    {
        int i1 = 1, i2 = 2, i3 = 3;

        // Combinations are not commutative.
        REQUIRE(hash_combine(i1, i2, i3) != hash_combine(i3, i2, i1));
    }

    SUBCASE("nonassociative")
    {
        int i1 = 1, i2 = 2, i3 = 3;

        // Combinations are not associative.
        REQUIRE(hash_combine(i1, i2, i3) != hash_combine(hash_combine(i1, i2), i3));
    }

    SUBCASE("iterators")
    {
        int i1 = 1, i2 = 2, i3 = 3;
        std::vector<int> v1{i1, i2, i3};

        // Overload for iterators.
        REQUIRE(hash_combine(v1.begin(), v1.end()) == hash_combine(i1, i2, i3));

        // Overload for pointers.
        int *p1 = v1.data(), *p2 = v1.data() + v1.size();
        REQUIRE(hash_combine(p1, p2) == hash_combine(i1, i2, i3));
    }
}
