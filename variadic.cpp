#include <iostream>
#include <type_traits>

template< typename T > void print(const T& v)
{
    std::cout << v << "\t\t";

    if (std::is_same<T, int>::value)
    {
        std::cout << "\t - int";
    }
    else if (std::is_same<T, double>::value)
    {
        std::cout << "\t - double";
    }
    else if (std::is_same<T, char>::value)
    {
        std::cout << " - char";
    }
    else if (std::is_same<T, const char*>::value)
    {
        std::cout << " - const char*";
    }
    else
    {
        std::cout << " - unknown";
    }

    std::cout << std::endl;
}

template<
    typename FIRST,
    typename... REST
>
void print(const FIRST& first, const REST&... rest)
{
    print(first);
    print(rest...);
}

void test2()
{
    print(123, 78.46, (const char*)"hello world!", std::addressof(std::cout), '\t');
    /*
123                      - int
78.46                    - double
hello world!             - const char*
7901B990                 - unknown
                         - char

D:\projects\devnull\cpp_cmd\vs\Debug\vs.exe (process 21260) exited with code 0.
Press any key to close this window . . .

    */
}