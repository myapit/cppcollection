#include <iostream>
#include <algorithm>

int main()
{
    // (1)
    std::cout << [](int a, int b){return a*b; }(4, 5) << std::endl; // 20

    // (2)
    auto f = [](int a, int b) { return a*b; };
    std::cout << f(4, 5) << std::endl;  // 20
}