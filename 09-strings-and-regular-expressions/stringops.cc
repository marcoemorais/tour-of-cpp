// Demonstrate operations in std::string.
#include <bitset>
#include <string>
#include <charconv>
#include <cstring>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

TEST_CASE("[stringops]")
{
    using namespace std::string_literals; // Required.

    SUBCASE("substr")
    {
        std::string hello{"Hello world"};

        // substr takes parameters: pos, size
        REQUIRE(hello.substr(0, hello.size()) == hello);
        // Not an error for size to extend past end of string.
        REQUIRE(hello.substr(0, hello.size()+10) == hello);
        // Not an error for substr to be empty.
        REQUIRE(hello.substr(0, 0) == std::string{});
    }

    SUBCASE("replace")
    {
        // NOTE: Unlike substr which returns new string, replace returns *this.

        // replace with same size substring.
        std::string hello1{"Hello world"};
        REQUIRE(hello1.replace(0, 5, "12345") == "12345 world"s);

        // replace with smaller substring.
        std::string hello2{"Hello world"};
        REQUIRE(hello2.replace(0, 5, "123") == "123 world"s);

        // replace with larger substring.
        std::string hello3{"Hello world"};
        REQUIRE(hello3.replace(0, 5, "1234567") == "1234567 world"s);
    }

    SUBCASE("conversions")
    {
        std::string s1{"10"};
        REQUIRE(std::stoi(s1) == 10);

        std::string s2{"3.14"};
        REQUIRE(std::stod(s2) == 3.14);

        int x = 20;
        REQUIRE(std::to_string(x) == "20"s);

        double y = 6.0;
        REQUIRE(std::to_string(y) == "6.000000"s); // Uses %f conversion.
    }

    SUBCASE("from_chars")
    {
        // C++17 adds from_chars as a replacement for stoi, stod.
        // Both stoi and stod will raise exceptions when failing to parse,
        // but from_chars returns an error code rather than raising.

        SUBCASE("int")
        {
            SUBCASE("no error")
            {
                std::string s1{"42"};
                int i1{0};
                auto [ptr, ec] = std::from_chars(s1.data(),
                                                 s1.data() + s1.size(),
                                                 i1);
                REQUIRE(ec == std::errc()); // No error.
                REQUIRE(i1 == 42);
            }

            SUBCASE("invalid_argument")
            {
                std::string s1{"abc"};
                int i1{0};
                auto [ptr, ec] = std::from_chars(s1.data(),
                                                 s1.data() + s1.size(),
                                                 i1);
                REQUIRE(ec == std::errc::invalid_argument);
            }

            SUBCASE("out_of_range")
            {
                std::string s1{"2147483648"}; // INT_MAX + 1
                int i1{0};
                auto [ptr, ec] = std::from_chars(s1.data(),
                                                 s1.data() + s1.size(),
                                                 i1);
                REQUIRE(ec == std::errc::result_out_of_range);
            }
        }

        SUBCASE("double")
        {
            SUBCASE("no error")
            {
                std::string s1{"3.14"};
                double d1{0.};
                auto [ptr, ec] = std::from_chars(s1.data(),
                                                 s1.data() + s1.size(),
                                                 d1);
                REQUIRE(ec == std::errc()); // No error.
                REQUIRE(d1 == 3.14);
            }

            SUBCASE("invalid_argument")
            {
                std::string s1{"abc"};
                double d1{0.};
                auto [ptr, ec] = std::from_chars(s1.data(),
                                                 s1.data() + s1.size(),
                                                 d1);
                REQUIRE(ec == std::errc::invalid_argument);
            }

            SUBCASE("out_of_range")
            {
                std::string s1{"1.79770e+308"}; // DBL_MAX + 1
                double d1{0.};
                auto [ptr, ec] = std::from_chars(s1.data(),
                                                 s1.data() + s1.size(),
                                                 d1);
                REQUIRE(ec == std::errc::result_out_of_range);
            }
        }
    }

    SUBCASE("bitstring to number")
    {
        SUBCASE("unsigned 8-bit integer")
        {
            auto bits = "10011100"s;
            std::uint8_t num;
            int base = 2;
            auto [ptr, ec] = std::from_chars(bits.data(),
                                             bits.data() + bits.size(),
                                             num,
                                             base);
            REQUIRE(ec == std::errc());
            REQUIRE(num == 156U);
        }

        SUBCASE("signed 8-bit integer")
        {
            auto bits = "10011100"s;
            int base = 2;
            std::int8_t num = std::stoi(bits.c_str(), nullptr, base);
            // Bug found in std::from_chars when type is int8_t and base=2.
            // auto [ptr, ec] = std::from_chars(bits.data(),
            //                                  bits.data() + bits.size(),
            //                                  num,
            //                                  base);
            // REQUIRE(ec == std::errc());
            REQUIRE(num == -100);
        }

        SUBCASE("single precision float")
        {
            auto bits = "01000000011000000000000000000000"s;
            std::uint32_t mem;
            int base = 2;
            auto [ptr, ec] = std::from_chars(bits.data(),
                                             bits.data() + bits.size(),
                                             mem,
                                             base);
            REQUIRE(ec == std::errc());
            float fp;
            std::memcpy(&fp, &mem, sizeof(mem));
            REQUIRE(fp == 3.5f);
        }
    }

    SUBCASE("number to bitstring")
    {
        SUBCASE("unsigned 8-bit integer")
        {
            std::uint8_t num{156};
            std::bitset<8> bits(num);
            REQUIRE(bits.to_string() == "10011100"s);
        }

        SUBCASE("signed 8-bit integer")
        {
            std::int8_t num{-100};
            std::bitset<8> bits(num);
            REQUIRE(bits.to_string() == "10011100"s);
        }

        SUBCASE("single precision float")
        {
            float fp = -32.75f;
            std::uint32_t mem;
            memcpy(&mem, &fp, sizeof(fp));
            std::bitset<8 * sizeof(mem)> bits(mem);
            REQUIRE(bits.to_string() == "11000010000000110000000000000000"s);
        }
    }
}
