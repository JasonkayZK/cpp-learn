g++ add_item2.cc -Wall -std=c++11 -o add_item2

echo "add success:"
./add_item2 < add_item_data.txt

echo "add fail:"
./add_item2 < add_item_data2.txt