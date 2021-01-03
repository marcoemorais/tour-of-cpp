// Implement typesafe version of printf using variadic templates.
#include <cmath>
#include <iostream>

// printf is a typesafe version of printf using variadic templates.
template <typename T, typename ... Tail>
void printf(T head, Tail... tail)
{
    std::cout << head << ' '; // Uses overloaded operator<< to print head.
    if constexpr(sizeof...(tail) > 0) { // Compile-time check on size of tail.
        printf(tail...);
    } else{
        std::cout << '\n';
    }
}

int main()
{
   constexpr double pi = 2.*std::acos(0.);
   std::string msg{"Hello World"};
   int meaning_of_life = 42;
   // Output:
   // 3.14159 Hello World 42
   printf(pi, msg, meaning_of_life);
}
