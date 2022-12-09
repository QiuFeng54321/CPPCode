#include <iostream>
#include <cmath>

int main() {
    int h;
    std::cin >> h;
    std::cout << h + h * (1 - pow(0.5, 9)) * 2 << std::endl;
    std::cout << h * pow(0.5, 10) << std::endl;
}