#include <iostream>

/**
 * 
 * ex: 153 = 1 ^ 3 + 5 ^ 3 + 3 ^ 3
 * 
 */

int main()
{
    int check = 0;
    int num_copy;
    int num, digit;
    std::cout << "Num: ";
    std::cin >> num;
    num_copy = num;
    while ((digit = (num % 10)) or num != 0)
    {
        check += digit * digit * digit;
        num = (num - num % 10) / 10; // Right shift a digit (right removal)
        std::cout << "num: " << num << ", digit: " << digit << std::endl;
    }

    std::cout << std::boolalpha << (check == num_copy) << std::endl;
}
