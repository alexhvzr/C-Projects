/*------------------------------- poly.cpp ---------------------------------------------------------/
 * Author   : Alex van Zuiden-Rylander                                                              /
 * Class    : CSS 343 B Spring 2019 | Data Structures, Algorithms, Discrete Mathematics 2           /
 * Started  : April 2, 2019                                                                         /
 * Modified : April 2, 2019                                                                         /
 * -------------------------------------------------------------------------------------------------/
 * Purpose  : This class was written in to allow the user to create polynomials. The user           /
 *            can add, subtract, multiply, compare and make deep copies of polynomials.             /
 * -------------------------------------------------------------------------------------------------/
 * Notes    : This program assumes that all passed values are integers. It also assumes             /
 *            that any given input of numbers using the input stream will end in -1 -1 to           /
 *            show signal there is no more input to read.                                           /
 --------------------------------------------------------------------------------------------------*/

#include "poly.h"
#include <math.h>
#include <stdlib.h>

bool isValid(int degree){
    return (degree <= 0);
}

/*---------------------------------- Output Overload -----------------------------------------------/
 * Prints the polynomial in sorted order.                                                           /
 --------------------------------------------------------------------------------------------------*/
ostream &operator<<(ostream &os, const Poly &p) {
    bool hasValue = false;
    bool first = true;
    if (p.length == 1) {
        os << p.polyArr[0];
        return os;
    }

    for (int i = p.length-1; i >= 0; i--) {
        if (p.polyArr[i] == 0)
            continue;
        hasValue = true;
        if(first){
            (p.polyArr[i] > 0) ? os << "+" : os << "-";
        }
        else{
            (p.polyArr[i] > 0) ? os << " +" : os << " -";
        }
        first = false;
        (p.polyArr[i] < 0) ? os << p.polyArr[i] * -1 : os << p.polyArr[i] ;
        if (i > 0)
            os << "x";
        if (i > 1)
            os << "^" << i;
    }
    if (!hasValue) {
        os << "0";
    }

    return os;
}   // End of Output Overload

/*---------------------------------- Input Overload ------------------------------------------------/
 *  Takes in a string and converts to a polynomial expression.                                      /
 --------------------------------------------------------------------------------------------------*/
istream &operator>>(istream &is, Poly &p) {
    int coeff = 0;
    int deg = 0;
    int maxDeg = 0;
    free(p.polyArr);

    while(is >> coeff >> deg) {
        if(coeff == -1 && deg == -1)
            break;
        if(deg > maxDeg){
            maxDeg = deg;
            Poly placeHolder(p);
            p.polyArr = (int*) calloc (maxDeg-1,sizeof(int));
            p = placeHolder;
            p.length = maxDeg+1;
        }

        Poly temp(coeff, deg);
        p += temp;
    }
    return is;
}   // End of Input Overload

/*---------------------------------- Constructor ---------------------------------------------------/
 *  Default Constructor - Set to the zero polynomial/                                               /
 --------------------------------------------------------------------------------------------------*/
Poly::Poly() {
    polyArr = (int*) calloc (1,sizeof(int));
    length = 1;
}   // End of Constructor

/*---------------------------------- Constructor ---------------------------------------------------/
 *  Constructor that takes in one parameter, the coefficient.                                       /
 --------------------------------------------------------------------------------------------------*/
Poly::Poly(int coeff) {
    polyArr = (int*) calloc (1,sizeof(int));
    length = 1;
    polyArr[0] = coeff;

}   // End of Constructor

/*---------------------------------- Constructor ---------------------------------------------------/
 *  Constructor that has a given coefficient and degree.                                            /
 --------------------------------------------------------------------------------------------------*/
Poly::Poly(int coeff, int deg) {
    if(isValid(deg)){
        polyArr = (int*) calloc (1,sizeof(int));
        length = 1;
    } else {
        polyArr = (int*) calloc (deg+1,sizeof(int));
        length = deg + 1;
        polyArr[deg] = coeff;
    }
}   // End of Constructor

/*---------------------------------- Constructor ---------------------------------------------------/
 *  Creates a deep Copy of another polynomial.                                                      /
 --------------------------------------------------------------------------------------------------*/
Poly::Poly(Poly &rhs) {
    length = rhs.length;
//    free(polyArr);
    polyArr = (int*) calloc (rhs.length,sizeof(int));

    for(int i = 0; i < rhs.length; i++){
        polyArr[i] = rhs.polyArr[i];
    }
}   // End of Constructor


/*---------------------------------- Destructor ----------------------------------------------------/
 *  Deletes the dynamically created array.                                                          /
 --------------------------------------------------------------------------------------------------*/
Poly::~Poly() {
       free(polyArr);
}   // End of Destructor

/*---------------------------------- Plus Arithmetic Operation -------------------------------------/
 *  Adds two polynomials together.                                                                  /
 --------------------------------------------------------------------------------------------------*/
Poly Poly::operator+(const Poly &rhs) {

    int shorter, longer;
    bool lhsShorter = false;

    if(length < rhs.length){
        longer = rhs.length;
        shorter = length;
        lhsShorter = true;
    } else {
        longer = length;
        shorter = rhs.length;
    }

    Poly temp(0, longer-1);

    for (int a = 0; a < shorter; a++) {
        temp.polyArr[a] = (polyArr[a] + rhs.polyArr[a]);
    }

    if (lhsShorter) {
        for (int i = shorter; i < longer; i++) {
            temp.polyArr[i] = rhs.polyArr[i];
        }
    } else {
        for (int i = shorter; i < longer; i++) {
            temp.polyArr[i] = polyArr[i];

        }
    }
    return temp;
}   // End of Plus Arithmetic Operation

/*---------------------------------- Minus Arithmetic Operation ------------------------------------/
 *  Subtracts two polynomials from each  other.                                                     /
 --------------------------------------------------------------------------------------------------*/
Poly Poly::operator-(const Poly &rhs) {
    int shorter, longer;
    bool lhsShorter = false;

    if(length < rhs.length){
        longer = rhs.length; shorter = length;
        lhsShorter = true;
    } else{
        longer = length, shorter = rhs.length;
    }

    Poly temp(0, longer-1);


    for (int a = 0; a < shorter; a++) {
        temp.polyArr[a] = (polyArr[a] - rhs.polyArr[a]);
    }

    if (lhsShorter) {
        for (int i = shorter; i < longer; i++) {
            temp.polyArr[i] = rhs.polyArr[i];
        }
    } else {
        for (int i = shorter; i < longer; i++) {
            temp.polyArr[i] = polyArr[i];
        }
    }
    return temp;
}   // End of Minus Arithmetic Operation

/*---------------------------------- Times Arithmetic Operation ------------------------------------/
 *  Returns the product of two polynomials.                                                         /
 --------------------------------------------------------------------------------------------------*/
Poly Poly::operator*(const Poly &rhs) {
    int shorter, longer;
    bool lhsShorter = false;

    if(length < rhs.length){
        longer = rhs.length;
        shorter = length;
        lhsShorter = true;
    } else {
        longer = length;
        shorter = rhs.length;
    }


    Poly temp(0, length-1 + rhs.length-1);


    if(lhsShorter){
        if(length==1){
            for(int i = 0; i < longer; i ++){
                temp.setCoeff(polyArr[0] * rhs.polyArr[i], i);
            }
        } else {
            for (int i = 0; i < shorter; i++) {
                for (int j = 0; j < longer; j++) {
                    temp.setCoeff(polyArr[i] * rhs.polyArr[j], i + j);
                }
            }
        }
    } else {
        if(rhs.length==1){
            for(int i = 0; i < longer; i ++){
                temp.setCoeff(polyArr[i] * rhs.polyArr[0], i);
            }
        } else {
            for (int i = 0; i < shorter; i++) {
                for (int j = 0; j < longer; j++) {
                    temp.setCoeff(polyArr[j] * rhs.polyArr[i], i + j);
                }
            }
        }
    }

    return temp;

}   // End of Times Arithmetic Operation

/*---------------------------------- Plus Equals Arithmetic Operation ------------------------------/
 *  Adds two polynomials together, making the lhs polynomial equal to lhs + rhs.                    /
 --------------------------------------------------------------------------------------------------*/
Poly Poly::operator+=(const Poly &rhs) {
    *this = (*this + rhs);
    return *this;
}   // End of Plus Equals Arithmetic Operation

/*---------------------------------- Minus Equals Arithmetic Operation -----------------------------/
 *  Subtracts the rhs polynomial from the lhs.                                                      /
 --------------------------------------------------------------------------------------------------*/
Poly Poly::operator-=(const Poly &rhs) {
    *this = (*this - rhs);
    return *this;
}   // End of Minus Equals Arithmetic Operation

/*---------------------------------- Times Equals Arithmetic Operation -----------------------------/
 *  Changes to lhs poly to equal lhs * rhs.                                                         /
 --------------------------------------------------------------------------------------------------*/
Poly Poly::operator*=(const Poly &rhs) {
    *this = (*this * rhs);
    return *this;
}   // End of Times Equals Arithmetic Operation

/*---------------------------------- Assignment Operator -------------------------------------------/
 *  Assigns one polynomial to another.                                                              /
 --------------------------------------------------------------------------------------------------*/
Poly Poly::operator=(const Poly &rhs) {
    length = rhs.length;
//    free(polyArr); ///////////////////////////////////////////////////////
    polyArr = (int*) calloc (rhs.length,sizeof(int));

    for(int i = 0; i < rhs.length; i++){
        polyArr[i] = rhs.polyArr[i];
    }
    return *this;
}   // End of operator =

/*---------------------------------- Less-than Operator --------------------------------------------/
 *  This determines if a polynomial is less than another.                                           /
 *  Assumptions: x is a positive number. That way evey value is evaluated to it's degree.           /
 --------------------------------------------------------------------------------------------------*/
bool Poly::operator<(const Poly &rhs) const {
int lhsVal = 0, rhsVal = 0;
for(int i = 0; i <= length; i++){
    lhsVal += (int)pow(polyArr[i],i);
}
for(int j = 0; j <= rhs.length; j++){
    rhsVal += (int)pow(rhs.polyArr[j],j);
}
   return (lhsVal < rhsVal);
}   // End of operator <

/*---------------------------------- Less-than or Equal to Operator --------------------------------/
 *  Checks if it's less than or equal to.                                                           /
 --------------------------------------------------------------------------------------------------*/
bool Poly::operator<=(const Poly &rhs) const {
    return (*this < rhs ||
            *this == rhs);
}   // End of operator <=

/*---------------------------------- Greater-than Operator -----------------------------------------/
 *  Checks if it's greater than.                                                                    /
 --------------------------------------------------------------------------------------------------*/
bool Poly::operator>(const Poly &rhs) const {
    return !(*this < rhs);
}   // End of operator >

/*---------------------------------- Greater-than or Equal to Operator -----------------------------/
 *  Checks if it's greater than or equal to.                                                        /
 --------------------------------------------------------------------------------------------------*/
bool Poly::operator>=(const Poly &rhs) const {
    return (*this > rhs ||
            *this == rhs);
}    // End of operator >=

/*---------------------------------- Equality Operator ---------------------------------------------/
 *  Checks if both polynomials are equal.                                                           /
 *  Assumes: that the polynomials might have been changed in length and checks both entire          /
 *  dynamically created arrays.                                                                     /
 --------------------------------------------------------------------------------------------------*/
bool Poly::operator==(const Poly &rhs) const {

    bool lhsShorter = false;
    int longer, shorter;
    if(length < rhs.length){
        longer = rhs.length;
        shorter = length;
        lhsShorter = true;
    } else {
        longer = length;
        shorter = rhs.length;
    }

    for(int i = 0; i < shorter; i++){
        if(polyArr[i] != rhs.polyArr[i])
            return false;
    }
    for(int j = shorter; j < longer; j++){
        if(lhsShorter){
            if(rhs.polyArr[j] != 0)
                return false;
        } else {
            if(polyArr[j] != 0)
                return false;
        }
    }

    return true;

}   // End of operator ==

/*---------------------------------- Not Equal Operator --------------------------------------------/
 *  Checks if two polynomials are not equal.                                                        /
 --------------------------------------------------------------------------------------------------*/
bool Poly::operator!=(const Poly &rhs) const {
    return !(*this == rhs);
}   // End of operator !=


/*---------------------------------- setCoeff Mutator ----------------------------------------------/
 *  Set's a coefficients value for a polynomial.                                                    /
 --------------------------------------------------------------------------------------------------*/
void Poly::setCoeff(int coeff, int deg) {
    if (deg > length) {

        Poly placeHolder(*this);
        free(polyArr);
        polyArr = (int*) calloc (deg-1,sizeof(int));
        for(int i = 0; i < length; i++)
            polyArr[i] = placeHolder.polyArr[i];
        length = deg+1;

    }
    polyArr[deg] = coeff;  // allows for multiple of the same polynomial to be entered.


}   // End of setCoeff

/*---------------------------------- getCoeff Accessor ---------------------------------------------/
 *  Get's the coefficient given the degree as an input.                                             /
 --------------------------------------------------------------------------------------------------*/
int Poly::getCoeff(int deg) {
    if(deg < 0)
        return 0;
    return polyArr[deg];
}   // End of getCoeff
