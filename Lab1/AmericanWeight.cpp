//
// Created by Alex Hayden van Zuiden-Rylander on 2019-01-11.
// This is a class that overloaded all of the operators for Weight <lbs, ozs>
//
#include "AmericanWeight.h"
#include <iostream>

using namespace std;

//input stream overload
istream &operator>>(istream &is, Weight &w) {
    is >> w.lbs >> w.ozs;
    w.reduce();
    return is;
}

ostream &operator<<(ostream &os, const Weight &w) {
    if (w.lbs == 0) {
        if (abs(w.ozs) == 1) {
            os << w.ozs << " oz";
        } else if (w.ozs != 0) {
            os << w.ozs << " ozs";
        } else {
            os << w.ozs << " oz";
        }
        return os;
    }
    if (abs(w.lbs) == 1) {
        os << w.lbs << " lb ";
        if (abs(w.ozs) == 1) {
            os << w.ozs << " oz";
        } else if (w.ozs != 0) {
            os << w.ozs << " ozs";
        }
        return os;
    }
    if (w.ozs == 0) {
        os << w.lbs << " lbs ";
        return os;
    }
    os << w.lbs << " lbs " << w.ozs << " ozs";
    return os;
}

Weight::Weight(Pounds x, Ounces y) {
    lbs = x;
    ozs = y;
    reduce();
}

Pounds Weight::getPounds() {
    return lbs;
}

Ounces Weight::getOunces() {
    return ozs;
}

void Weight::setPounds(Pounds pounds) {
    lbs = pounds;
}

void Weight::setOunces(Ounces oun) {
    ozs = oun;
}

Weight Weight::operator+(const Weight &w) const {
    Weight temp((lbs + w.lbs), (ozs + w.ozs));
    return temp;
}

Weight Weight::operator-(const Weight &w) const {
    Weight temp((lbs - w.lbs), (ozs - w.ozs));
    return temp;
}

Weight Weight::operator*(const double d) const {
    Weight temp;
    temp.ozs = (lbs * 16);
    temp.ozs += ozs;
    temp.ozs *= d;
    temp.reduce();
    return temp;
}

double Weight::operator/(const Weight &w) const {
    if (w.ozs == 0 && w.lbs == 0) {
        cout << "Zero divide! ";
        return -numeric_limits<double>::infinity();
    } else {
        return ((double) ((lbs*16) + ozs) / (double) ((w.lbs*16) + w.ozs));
    }
}

Weight Weight::operator/(const double d) const {
    Weight temp;
    if (d == 0) {
        cout << "Non-real answer, cannot divide by zero." << endl;
        return temp;
    } else {
        temp.ozs += (16 * lbs);
        if (temp.ozs < 0) {
            temp.ozs += ozs;
        } else {
            temp.ozs -= ozs;
        }
        temp.ozs /= d;
        temp.reduce();
        return temp;
    }
}

Weight Weight::operator-() const {
    Weight temp(-lbs, -ozs);
    temp.reduce();
    return temp;
}

bool Weight::operator==(const Weight &w) const {
    return lbs == w.lbs &&
           ozs == w.ozs;
}

bool Weight::operator!=(const Weight &w) const {
    return !(w == *this);
}

bool Weight::operator>(const Weight &w) const {
    return !(*this < w);
}

bool Weight::operator<(const Weight &w) const {
    if (w.lbs > lbs) {
        return true;
    }
    if (w.lbs == lbs && w.ozs > ozs) {
        return true;
    }
    return false;
}

bool Weight::operator>=(const Weight &w) const {
    if (*this == w || *this > w) {
        return true;
    }
    return false;
}

bool Weight::operator<=(const Weight &w) const {
    if (*this == w || *this < w) {
        return true;
    }
    return false;
}

Weight &Weight::operator+=(const Weight &w) {
    lbs += w.lbs;
    ozs += w.ozs;
    reduce();
    return *this;
}

Weight &Weight::operator-=(const Weight &w) {
    lbs -= w.lbs;
    ozs -= ozs;
    reduce();
    return *this;
}

Weight &Weight::operator*=(const double d) {
    ozs += (16 * lbs);
    lbs = 0;
    ozs *= d;
    reduce();
    return *this;
}

Weight &Weight::operator/=(const double d) {
    ozs += (16 * lbs);
    lbs = 0;
    ozs /= d;
    reduce();
    return *this;
}

void Weight::reduce() {
    lbs += ozs / 16;
    ozs %= 16;
    if (lbs > 0 && ozs < 0) {
        lbs--;
        ozs += 16;
    }
    if (lbs < 0 && ozs > 0) {
        lbs++;
        ozs -= 16;
    }
}