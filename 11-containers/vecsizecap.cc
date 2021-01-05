// Demonstrate size and capacity of std::vector with reserve, resize, clear, and shrink_to_fit.
#include <iostream>
#include <vector>

int main()
{
    // Output:
    // Default constructor, empty vector
    // size     : 0
    // capacity : 0
    // reserve increases capacity, but do not change size.
    // size     : 0
    // capacity : 10
    // resize increases size to match capacity.
    // size     : 10
    // capacity : 10
    // clear reduces size to 0, but does not change capacity.
    // size     : 0
    // capacity : 10
    // shrink_to_fit reduces capacity to match size eg 0.
    // size     : 0
    // capacity : 0
    std::vector<int> v;

    std::cout << "Default constructor, empty vector\n";
    std::cout << "size     : " << v.size() << '\n';
    std::cout << "capacity : " << v.capacity() << '\n';

    v.reserve(10);
    std::cout << "reserve increases capacity, but do not change size.\n";
    std::cout << "size     : " << v.size() << '\n';
    std::cout << "capacity : " << v.capacity() << '\n';

    v.resize(10);
    std::cout << "resize increases size to match capacity.\n";
    std::cout << "size     : " << v.size() << '\n';
    std::cout << "capacity : " << v.capacity() << '\n';

    v.clear();
    std::cout << "clear reduces size to 0, but does not change capacity.\n";
    std::cout << "size     : " << v.size() << '\n';
    std::cout << "capacity : " << v.capacity() << '\n';

    v.shrink_to_fit(); // C++11.
    std::cout << "shrink_to_fit reduces capacity to match size eg 0.\n";
    std::cout << "size     : " << v.size() << '\n';
    std::cout << "capacity : " << v.capacity() << '\n';
}
