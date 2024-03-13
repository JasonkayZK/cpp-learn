//
// Created by Jasonkay on 2022/6/10.
//

/* This file defines the sales_item class used in chapter 1.
 * The code used in this file will be explained in
 * Chapter 7 (Classes) and Chapter 14 (Overloaded Operators)
 * Readers shouldn't try to understand the code in this file
 * until they have read those chapters.
*/

#ifndef CPP_LEARN_SALES_ITEM_H
#define CPP_LEARN_SALES_ITEM_H

#include <iostream>
#include <string>

class sales_item {

    friend std::istream &operator>>(std::istream &, sales_item &);

    friend std::ostream &operator<<(std::ostream &, const sales_item &);

    friend bool operator<(const sales_item &, const sales_item &);

    friend bool operator==(const sales_item &, const sales_item &);

public:

    sales_item() = default;

    sales_item(const std::string &book) : bookNo(book) {}

    sales_item(std::istream &is) { is >> *this; }

public:
    // operations on sales_item objects
    // member binary operator: left-hand operand bound to implicit this pointer
    sales_item &operator+=(const sales_item &);

    // operations on sales_item objects
    std::string isbn() const { return bookNo; }

    double avg_price() const;

private:
    std::string bookNo;      // implicitly initialized to the empty string
    unsigned units_sold = 0; // explicitly initialized
    double revenue = 0.0;
};

// used in chapter 10
inline bool compareIsbn(const sales_item &lhs, const sales_item &rhs) {
    return lhs.isbn() == rhs.isbn();
}

// nonmember binary operator: must declare a parameter for each operand
sales_item operator+(const sales_item &, const sales_item &);

inline bool operator==(const sales_item &lhs, const sales_item &rhs) {
    // must be made a friend of sales_item
    return lhs.units_sold == rhs.units_sold &&
           lhs.revenue == rhs.revenue &&
           lhs.isbn() == rhs.isbn();
}

inline bool operator!=(const sales_item &lhs, const sales_item &rhs) {
    return !(lhs == rhs); // != defined in terms of operator==
}

// assumes that both objects refer to the same ISBN
sales_item &sales_item::operator+=(const sales_item &rhs) {
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

// assumes that both objects refer to the same ISBN
sales_item operator+(const sales_item &lhs, const sales_item &rhs) {
    sales_item ret(lhs); // copy (|lhs|) into a local object that we'll return
    ret += rhs;          // add in the contents of (|rhs|)
    return ret;          // return (|ret|) by value
}

std::istream &operator>>(std::istream &in, sales_item &s) {
    double price;
    in >> s.bookNo >> s.units_sold >> price;
    // check that the inputs succeeded
    if (in)
        s.revenue = s.units_sold * price;
    else
        s = sales_item(); // input failed: reset object to default state
    return in;
}

std::ostream &operator<<(std::ostream &out, const sales_item &s) {
    out << s.isbn() << " " << s.units_sold << " " << s.revenue << " " << s.avg_price();
    return out;
}

double sales_item::avg_price() const {
    if (units_sold)
        return revenue / units_sold;
    else
        return 0;
}

#endif //CPP_LEARN_SALES_ITEM_H
