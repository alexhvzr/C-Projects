//
// Created by Alex Hayden van Zuiden-Rylander on 2019-01-16.
//
// This class is a distance class that overrides all meaningful operators.
// The distances are in american measurements, <ft,in>
// Inches cannot be equal too or larger than 12.
//

#include "Distance.h"
#include <iostream>

using namespace std;

//Input stream operator overload
istream &operator>>(istream &is, Distance &d) {
    is >> d.ft >> d.in;
    d.reduce();
    return is;
}

//Output stream operator overload
ostream &operator<<(ostream &os, const Distance &d) {
    if (d.ft == 0) {
        if (abs(d.in) == 1) {
            os << d.in << " inch";
        }
        os << d.in << " inches";
        return os;
    }
    if (abs(d.ft) == 1) {
        os << d.ft << " ft ";
        if (abs(d.in) == 1) {
            os << d.in << " inch";
        } else if (d.in != 0) {
            os << d.in << " inches";
        }
        return os;
    }
    if (d.in == 0) {
        os << d.ft << " ft ";
        return os;
    }
    os << d.ft << " ft " << d.in << " inches";
    return os;
}

/*
 * Constructor for the distance class.
 * Sets private data members equal to input.
 */
Distance::Distance(Feet f, Inches i) {
    ft = f;
    in = i;
    reduce();
}

/*
 * Below this are the setters and getters for the distance class.
 * Public so that the end user can make changes to weights.
 */
Feet Distance::getFeet() const {
    return ft;
}

Inches Distance::getInches() {
    return in;
}

void Distance::setFeet(Feet feet) {
    ft = feet;
}

void Distance::setInches(Inches inches) {
    in = inches;
}

/*
 * Unary negation takes the weight that it was in front of and makes its variables negative.
 */
Distance Distance::operator-() {
    Distance temp(-ft, -in);
    return temp;
}

/*
 * Adds two distances together, no need to reduce,
 * that's called when temp is made.
 */
Distance Distance::operator+(const Distance &d) const {
    Distance temp((ft + d.ft), (in + d.in));
    return temp;
}

/*
 * The left hand argument minus the right hand argument.
 * Returns the difference.
 */
Distance Distance::operator-(const Distance &d) const {
    Distance temp((ft - d.ft), (in - d.in));
    return temp;
}

/*
 * Division operator first checks to see if trying to divide by zero,
 * the returns the ratio between the two distances.
 */
double Distance::operator/(const Distance &d) const {
    if (d.in == 0 && d.ft == 0) {
        cout << "Zero divide! ";
        return -numeric_limits<double>::infinity();
    } else {
        return ((double) ((ft * 12) + in) / (double) ((d.ft * 12) + d.in));
    }
}

/*
 * This multiplication function returns the square feet to the nearest tenth of a foot.
 * First it calculates the ft squared, then the inches / 12 to find any extra footage.
 * Then there's the inches % 12 to find the nearest tenth of an inch.
 */
double Distance::operator*(const Distance &d) const {
    return (ft * d.ft) + ((in * d.in) / 12) + (.1 * ((in * d.in) % 12));
}

/*
 * This equality operator checks to see whether two distances are the same.
 */
bool Distance::operator==(const Distance &d) const {
    return ft == d.ft
           && in == d.in;
}

/*
 * Checks for inequality.
 */
bool Distance::operator!=(const Distance &d) const {
    return !(*this == d);
}

/*
 * This operator first see's if the right hand arguments feet are less
 * than the left hand side. Then if that's not true, it checks to see
 * if they are equal in feet, which argument has the longer inches.
 */
bool Distance::operator<(const Distance &d) const {
    if (ft < d.ft) {
        return true;
    } else if (ft == d.ft && in < d.in) {
        return true;
    }
    return false;
}

/*
 * Checks if the hand side is not less than.
 */
bool Distance::operator>(const Distance &d) const {
    return !(*this < d);
}

/*
 * With all the nessesary functions implimented
 * it checks for equality or greater than.
 */
bool Distance::operator>=(const Distance &d) const {
    return (*this == d || *this > d);
}

/*
 * With all the nessesary functions implimented
 * it checks for equality or less than.
 */
bool Distance::operator<=(const Distance &d) const {
    return (*this == d || *this < d);
}

/*
 * Changes to left hand side argument, adding the
 * argument (distance) passed in.
 */
Distance &Distance::operator+=(const Distance &d) {
    ft += d.ft;
    in += d.in;
    reduce();
    return *this;
}

/*
 * Changes to left hand side argument, subtracting the
 * argument (distance) passed in.
 */
Distance &Distance::operator-=(const Distance &d) {
    ft -= d.ft;
    in -= d.in;
    reduce();
    return *this;
}

/*
 * This method makes sure that the feet are converted
 * to proper length format.
 */
void Distance::reduce() {
    ft += in / 12;
    in %= 12;
    if (ft > 0 && in < 0) {
        ft--;
        in += 12;
    }
    if (ft < 0 && in > 0) {
        ft++;
        in -= 12;
    }
}
