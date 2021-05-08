//
// Created by jasonkay on 2021/5/8.
// c_str(): convert a string to char array(C-type String)

#include <string>
#include <fstream>
#include <iostream>

int main() {
    using namespace std;

    string filename;
    cout << "Enter file name: ";
    cin >> filename;

    ifstream fin;
    fin.open(filename.c_str());
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
