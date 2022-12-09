#include <iostream>

/**
 * 
 * ex: 15823 => 13582
 * 
 */

int main()
{
    int even = 0, odd = 0, even_digit = 0, odd_digit = 0;
    int even_mask = 1, odd_mask = 1;
    int num, digit;
    std::cout << "Num: ";
    std::cin >> num;
    while ((digit = (num % 10)) or num != 0)
    {
        if (digit % 2)
        { // odd
            odd += digit * odd_mask;
            odd_digit++;
            odd_mask *= 10;
        }
        else
        {
            even += digit * even_mask;
            even_digit++;
            even_mask *= 10;
        }
        std::cout << "odd: " << odd << ", even: " << even << std::endl;
        std::cout << "odd mask: " << odd_mask << ", even mask: " << even_mask << std::endl;
        num = (num - num % 10) / 10; // Right shift a digit (right removal)
        std::cout << "num: " << num << ", digit: " << digit << std::endl;
    }

    std::cout << odd * even_mask + even << std::endl;
}
