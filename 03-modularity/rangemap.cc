// Demonstrate use of unpacking and for-range syntax for map containers.
#include <iostream>
#include <unordered_map>

void for_rangemap1()
{
    std::unordered_map<std::string, int> m{
        {"one", 1},
        {"two", 2},
        {"three", 3}
    };

    // Use constant reference to pair.
    for (const auto& kv : m) {
        std::cout << "k=" << kv.first << " v=" << kv.second << "\n";
    }
}

void for_rangemap2()
{
    std::unordered_map<std::string, int> m{
        {"eleven", 11},
        {"twelve", 12},
        {"thirteen", 13}
    };

    // Use unpacking.
    for (const auto& [key, value] : m) {
        std::cout << "k=" << key << " v=" << value << "\n";
    }
}

int main()
{
    for_rangemap1();
    for_rangemap2();
}
