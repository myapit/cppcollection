#include <sstream>
#include <string>
#include <iostream>

int main() {
    std::ostringstream ss;
    long num = 123456;
    ss << num;
    std::cout << ss.str() << std::endl;
}
