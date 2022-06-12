//
// Created by Jasonkay on 2022/6/11.
//

#include <iostream>

int main() {

    int i = 42;
    std::cout << i << std::endl; // prints 42
    if (i) // condition will evaluate as true
        i = 0;
    std::cout << i << std::endl; // prints 0

    bool b = 42;            // b is true
    std::cout << b << std::endl; // prints 1

    int j = b;              // j has value 1
    std::cout << j << std::endl; // prints 1

    double pi = 3.14;       // pi has value 3.14
    std::cout << pi << std::endl; // prints 3.14

    j = pi;                 // j has value 3
    std::cout << j << std::endl; // prints 3

    unsigned char c = -1;   // assuming 8-bit chars, c has value 255
    i = c;  // the character with value 255 is an unprintable character
    // assigns value of c (i.e., 255) to an int
    std::cout << i << std::endl; // prints 255

    return 0;
}
