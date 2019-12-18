//
// Created by Alex Hayden van Zuiden-Rylander on 2019-01-16.
// This header file predefined all the operators and constructors used in the .CPP class.
//

#ifndef DISTANCE_DISTANCE_H
#define DISTANCE_DISTANCE_H

#include <iostream>

using namespace std;
typedef int Feet;
typedef int Inches;

class Distance {
    //class by default is private., so below are the private variables and functions.

    //Out stream operator
    friend ostream &operator<<(ostream &, const Distance &);

    //Input stream operator
    friend istream &operator>>(istream &, Distance &);

    //Private variables.
    Feet ft;
    Inches in;

    //Function to have Distance displayed properly.
    void reduce();

public:

    //Default constructor that sets weight to zero unless specified otherwise.
    Distance(Feet f = 0, Inches i = 0);

    //Setters and getters
    Feet getFeet() const;

    Inches getInches();

    void setFeet(Feet);

    void setInches(Inches);

    //unary negation
    Distance operator-();

    //basic arithmetic operators
    Distance operator+(const Distance &) const;

    Distance operator-(const Distance &) const;

    double operator/(const Distance &) const;

    double operator*(const Distance &) const;

    //Boolean equality operators
    bool operator==(const Distance &) const;

    bool operator!=(const Distance &) const;

    bool operator<(const Distance &) const;

    bool operator>(const Distance &) const;

    bool operator>=(const Distance &) const;

    bool operator<=(const Distance &) const;

    //Plus ande minus equals operators
    Distance &operator+=(const Distance &);

    Distance &operator-=(const Distance &);


};

#endif //DISTANCE_DISTANCE_H
