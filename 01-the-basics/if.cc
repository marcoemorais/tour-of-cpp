// Go-style variable declaration as part of `if`.
#include <iostream>
#include <vector>

bool
is_odd(int n)
{
    return n%2 != 0;
}

int main()
{
    // Output:
    // 0 even
    // 1 odd
    // 2 even
    // 3 odd
    // 4 even
    // 5 odd
    // 6 even
    std::vector<int> v{0,1,2,3,4,5,6};

    for (auto& x : v) {
        // If-statements can introduce new variables.
        if (auto odd = is_odd(x); odd) {
            std::cout << x << " odd\n";
        } else {
            std::cout << x << " even\n";
        }
    }
}
