#include <iostream>
#include <vector>

bool
is_odd(int n)
{
    return n%2 != 0;
}

int main()
{
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
