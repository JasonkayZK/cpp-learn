// 16.2 strfile.cpp
// Created by jasonkay on 2021/5/8.
//
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

int main() {
    using namespace std;

    ifstream fin;
    fin.open("../to_buy.txt");
    if (!fin.is_open()) {
        cerr << "Can't open file. Bye.\n";
        exit(EXIT_FAILURE);
    }

    string item;
    int count = 0;
    getline(fin, item, ':');
    while (fin) {
        ++count;
        cout << count << ": " << item << endl;
        getline(fin, item, ':');
    }

    cout << "Done\n";
    fin.close();

    return 0;
}
