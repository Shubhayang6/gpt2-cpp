#include <iostream>

int main()
{
    // Printing which compiler built the binary. Support for Linux and Windows
#if defined(_MSC_VER)
    std::cout << "gpt2-cpp | built with MSVC " << _MSC_VER << "\n";
#elif defined(__GNUC__)
    std::cout << "gpt2-cpp | built with g++ " << __VERSION__ << "\n";
#else
    std::cout << "gpt2-cpp | unknown compiler\n";
#endif
    return 0;
}
