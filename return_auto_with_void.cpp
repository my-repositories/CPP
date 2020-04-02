#include <iostream>
#include <type_traits>

template <class F>
auto debug(F f) {
    if constexpr (std::is_same<typename std::result_of<F & ()>::type, void>::value)
    {
        f();
        std::cout << "calle(void) debug" << std::endl;
    }
    else if constexpr (std::is_same<typename std::result_of<F & ()>::type, int>::value)
    {
        auto r = f();
        std::cout << "called(int) debug" << std::endl;
        return r;
    }
    else
    {
        auto r = f();
        std::cout << "called(unknown) debug" << std::endl;
        return r;
    }
}

int main()
{
    auto int_function = [] {std::cout << "lambda_int" << std::endl; return 571; };
    int res = debug(int_function);
    std::cout << res << std::endl << std::endl << std::endl;

    auto double_function = [] {std::cout << "lambda_double" << std::endl; return 571.3; };
    double resd = debug(double_function);
    std::cout << resd << std::endl << std::endl << std::endl;

    auto void_function = [] {std::cout << "lamba_void" << std::endl; };
    debug(void_function);

    return 0;
}

/*
lambda_int
called(int) debug
571


lambda_double
called(unknown) debug
571.3


lamba_void
calle(void) debug

D:\projects\devnull\cpp_cmd\vs\Debug\vs.exe (process 27292) exited with code 0.
Press any key to close this window . . .

*/