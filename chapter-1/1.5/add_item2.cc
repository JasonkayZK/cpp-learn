//
// Created by Jasonkay on 2022/6/10.
//


#include "sales_item.h"

#include <iostream>

int main() {
    sales_item book1, book2;

    std::cin >> book1 >> book2;

    if (book1.isbn() == book2.isbn()) {
        std::cout << book1 + book2 << std::endl;
        return 0;   // indicate success
    } else {
        std::cerr << "Data must refer to same ISBN" << std::endl;
        return -1;  // indicate failure
    }
}
