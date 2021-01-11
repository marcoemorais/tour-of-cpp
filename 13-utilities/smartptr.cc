// Demonstrate use of std::unique_ptr and std::shared_ptr.
#include <cstdlib>
#include <memory>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

TEST_CASE("[std::unique_ptr]")
{
    SUBCASE("init")
    {
        // Constructor taking *T as parameter.
        std::unique_ptr<int> pi1{new int(42)};
        REQUIRE(*pi1 == 42);

        // Factory function uses parameter forwarding to allocate new T.
        auto pi2 = std::make_unique<int>(42);
        REQUIRE(*pi2 == 42);
    }

    SUBCASE("assignment")
    {
        auto pi1 = std::make_unique<int>(1);
        auto pi2 = std::make_unique<int>(42);

        pi1 = std::move(pi2); // Deallocate pi1 and transfer pi2 to pi1.
        REQUIRE(bool(pi1) == true);
        REQUIRE(*pi1 == 42);
        REQUIRE(bool(pi2) == false);
    }

    SUBCASE("custom deleter")
    {
        using T = int;

        // alloc_func and free_func mimic C-style API.
        auto alloc_func = []() -> T* {
            return static_cast<T*>(std::malloc(sizeof(T)));
        };
        auto free_func = [](T* ptr) { std::free(ptr); };
        std::unique_ptr<T, std::function<void(T*)>> pi1(alloc_func(), free_func);
        REQUIRE(bool(pi1) == true);

        pi1.reset(); // Deletes the managed object.
        REQUIRE(bool(pi1) == false);
    }
}

TEST_CASE("[std::shared_ptr]")
{
    SUBCASE("init")
    {
        // Constructor taking *T as parameter.
        std::shared_ptr<int> pi1{new int(42)};
        REQUIRE(*pi1 == 42);

        // Factory function uses parameter forwarding to allocate new T.
        auto pi2 = std::make_shared<int>(42);
        REQUIRE(*pi2 == 42);
    }

    SUBCASE("use_count")
    {
        auto pi1 = std::make_shared<int>(1);
        REQUIRE(bool(pi1) == true);
        REQUIRE(pi1.use_count() == 1);

        auto pi2 = pi1; // pi1 and pi2 point to the same (shared) reference.
        REQUIRE(pi1.use_count() == 2);
        REQUIRE(pi2.use_count() == 2);

        // Create an additional reference in an inner scope.
        {
            auto pi3 = pi1;
            REQUIRE(pi3.use_count() == 3);
            REQUIRE(pi1.use_count() == 3);
        } // Decrement reference count.
        REQUIRE(pi1.use_count() == 2);
        REQUIRE(pi2.use_count() == 2);
    }

    SUBCASE("conversion")
    {
        using T = int;

        // Common for factory functions to return std::unique_ptr.
        // Return value can be assigned to std::unique_ptr or std::shared_ptr.
        auto factory_func = []() -> std::unique_ptr<T> {
            return std::make_unique<T>(T());
        };
        std::shared_ptr<T> sp1 = factory_func(); // Assignment from unique_ptr to shared_ptr.
        REQUIRE(bool(sp1) == true);
        REQUIRE(*sp1 == T());

        std::shared_ptr<T> sp2 = std::make_unique<T>(T());
        REQUIRE(bool(sp2) == true);
        REQUIRE(*sp2 == T());
    }
}
