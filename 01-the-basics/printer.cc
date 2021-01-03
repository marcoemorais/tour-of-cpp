// Template for printing containers.
#include <iostream>
#include <iterator>
#include <vector>
#include <unordered_map>
#include <string>
#include <utility>

// printer prints elements from [first, last).
template <typename FwdIter>
std::ostream&
printer(std::ostream& os, FwdIter first, FwdIter last, const std::string& name="")
{
    std::string delim;
    os << name << " = {";
    while (first != last) {
        os << delim << *first;
        delim = ", ";
        ++first;
    }
    os << "}\n";
    return os;
}

// operator<< for std::pair.
template <typename T1, typename T2>
std::ostream&
operator<<(std::ostream& os, const std::pair<T1, T2>& entry)
{
    os << "(" << entry.first << "," << entry.second << ")";
    return os;
}

int main()
{
    std::vector<int> v1{1,2,3,4,5};
    printer(std::cout, std::begin(v1), std::end(v1), "v1");

    std::vector<std::string> v2{"one","two","three","four","five"};
    printer(std::cout, std::begin(v2), std::end(v2), "v2");

    std::unordered_map<std::string, int> m1{
        {"one", 1},
        {"two", 2},
        {"three", 3},
        {"four", 4},
        {"five", 5},
    };
    printer(std::cout, std::begin(m1), std::end(m1), "m1");

    std::unordered_map<int, std::string> m2{
        {1, "one"},
        {2, "two"},
        {3, "three"},
        {4, "four"},
        {5, "five"},
    };
    printer(std::cout, std::begin(m2), std::end(m2), "m2");
}
