// Read a file line-by-line raising std::runtime_error if error.
#include <algorithm>
#include <cerrno>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// read_lines returns vector of lines from file or throws.
std::vector<std::string>
read_lines(const std::string& filename)
{
    std::ifstream is{filename};
    if (!is.is_open()) {
        throw std::runtime_error{strerror(errno)};
    }

    std::vector<std::string> lines;
    for (std::string line; getline(is, line); ) {
        lines.emplace_back(line);
    }

    if (is.bad()) {
        throw std::runtime_error{strerror(errno)};
    }

    return lines;
}

TEST_CASE("[read_lines]")
{
    // Create a file used to exercise read_lines.
    std::string filename{"readfile_test.txt"};
    std::vector<std::string> lines{
        "line number 1",
        "line number 2",
        "line number 3",
        "line number 4",
        "line number 5",
    };

    // Setup.
    {
        std::ofstream os{filename};
        std::copy(lines.begin(), lines.end(),
                  std::ostream_iterator<std::string>(os, "\n"));
    }

    SUBCASE("read_lines successfully reads file")
    {
        auto rcv = read_lines(filename);
        REQUIRE(rcv.size() == lines.size());
        REQUIRE(rcv == lines);
    }

    SUBCASE("read_lines throws")
    {
        using namespace std::string_literals;
        REQUIRE_THROWS_AS(read_lines("file_does_not_exist.txt"s),
                          std::runtime_error);
    }

    std::remove(filename.c_str());
}
