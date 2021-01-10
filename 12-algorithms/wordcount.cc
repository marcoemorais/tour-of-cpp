// Emit word frequency count based on input read from stdin.
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <map>

int main()
{
    std::map<std::string, int> wc;
    std::for_each(std::istream_iterator<std::string>(std::cin),
                  std::istream_iterator<std::string>(),
                  [&wc](const auto& s) { wc[s] += 1; });
    for (const auto& [word, count] : wc) {
        std::cout << word << ": " << count << '\n';
    }
}
