//
// Created by Jasonkay on 2022/6/10.
//

#include <iostream>

int main() {

    int sum = 0, val = 0;
    while (std::cin >> val) {
        sum += val;
    }
    std::cout << "Sum is: " << sum << std::endl;

    return 0;
}
