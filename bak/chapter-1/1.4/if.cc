//
// Created by Jasonkay on 2022/6/10.
//

#include <iostream>

int main() {

    int cur_val = 0, val = 0;
    if (std::cin >> cur_val) {
        int cnt = 1;

        while (std::cin >> val) {
            if (cur_val == val) {
                ++cnt;
            } else {
                std::cout << cur_val << " occurs " << cnt << " times" << std::endl;
                cur_val = val;
                cnt = 1;
            }
        }
        std::cout << cur_val << " occurs " << cnt << " times" << std::endl;
    }

    return 0;
}
