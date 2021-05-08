// 16.1 str1.cpp
// Created by jasonkay on 2021/5/7.
//
#include <string>
#include <algorithm>
#include <iostream>

int main() {
    using namespace std;

    // ctor #1
    string one("Lottery Winner!");
    cout << one << endl; // overloaded <<

    // ctor #2
    string two(20, '$');
    cout << two << endl;

    // ctor #3
    string three(one);
    cout << three << endl;

    // overloaded +=
    one += " Oops!";
    cout << one << endl;

    // ctor #4
    two = "Sorry! That was ";
    three[0] = 'p';
    string four;
    four = two + three;
    cout << four << endl;

    // ctor #5
    char allStr[] = "All's well that ends well";
    string five(allStr, 20);
    cout << five << "!\n";

    // ctor #6
    string six(allStr + 6, allStr + 10);
    cout << six << ", ";

    // ctor #6 again
    string seven(&five[6], &five[10]);
    cout << seven << "...\n";

    // ctor #7
    string eight(four, 7, 16);
    cout << eight << " in motion!" << endl;

    cout << "max string length: " << string::npos << endl;

    return 0;
}
