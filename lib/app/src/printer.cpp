#include "../inc/printer.hpp"

void print(int c)
{
    std::cout << c << std::endl;
    std::cout << test1(c) << std::endl;

    test2(&c);

    std::cout << c << std::endl;
    std::cout << test1(c) << std::endl;
}
