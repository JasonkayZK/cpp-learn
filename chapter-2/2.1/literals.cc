//
// Created by Jasonkay on 2022/6/11.
//

#include <iostream>

int main() {
    std::cout << "Hello World!";  // simple character string literal
    std::cout << "";              // empty character string literal

    // literal using newlines and tabs
    std::cout << "\nCC\toptions\tfile.[cC]\n";

    // multiline string literal
    std::cout << "a really, really long string literal "
                 "that spans two lines" << std::endl;

    // three ways to print a capital M
    std::cout << 'M' << " " << '\115' << " " << '\x4d' << std::endl;

    // Some char types
    wchar_t a = L'a'; // wide character
    char16_t c = u'a'; // unicode 16
    char32_t d = U'a'; // unicode 32
//    char8_t e[] = u8"hi!";  // UTF-8

    unsigned long long x = 42ULL;
    float y = 1E-3F;
    long double z = 3.1415L;

    unsigned long long bigVal = -1ULL;
    std::cout << bigVal << std::endl;

    return 0;
}
