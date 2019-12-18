//
// Created by Alex Hayden van Zuiden-Rylander on 2019-01-11.
//

#ifndef LAB1_AMERICANWEIGHT_H
#define LAB1_AMERICANWEIGHT_H

#include <iostream>
using namespace std;
typedef int Pounds;
typedef int Ounces;
class Weight {

// Overloaded output operator: prints x lbs y ozs, 1 lb 1 oz, x lbs, y ozs, or 0 oz
    friend ostream &operator<<(ostream &, const Weight &);

// Overloaded input operator: takes two integers as lbs and ozs.
    friend istream &operator>>(istream &, Weight &);

// Private data members
    Pounds lbs;
    Ounces ozs;

// Reduce Ounces in up to 16 ozs
    void reduce();

public:
// Constructor: the default is 0 lb 0 oz
    Weight(Pounds x = 0, Ounces y = 0);

// Get methods
    Pounds getPounds();

    Ounces getOunces();

// set methods
    void setPounds(Pounds); // optional
    void setOunces(Ounces); // optional

// Arithmetic operators
    Weight operator+(const Weight &) const;

    Weight operator-(const Weight &) const;

    Weight operator*(double) const;

    double operator/(const Weight &) const;

    Weight operator/(double) const;

    Weight operator-() const;

// Boolean comparison operators
    bool operator==(const Weight &) const;

    bool operator!=(const Weight &) const;

    bool operator>(const Weight &) const;

    bool operator<(const Weight &) const;

    bool operator>=(const Weight &) const;

    bool operator<=(const Weight &) const;

// Assignment operators
    Weight &operator+=(const Weight &);

    Weight &operator-=(const Weight &);

    Weight &operator*=(double);

    Weight &operator/=(double);

};
#endif //LAB1_AMERICANWEIGHT_H
