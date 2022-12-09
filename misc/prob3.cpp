#include <iostream>

/**
 * 
 * Q: num is prime?
 * 
 */

bool is_prime(int num) {
    if (num == 1 or num == 2) return true;
    if (num % 2 == 0) return false;
    for (int i = 3; i < num; i += 2) {
        if (num % i == 0) return false;
    }
    return true;
}

int main()
{
    int num;
    std::cout << "Num: ";
    std::cin >> num;
    std::cout << std::boolalpha << is_prime(num) << std::endl;
}
