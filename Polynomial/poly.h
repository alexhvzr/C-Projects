/*------------------------------- poly.h ---------------------------------------------------/
 * Author   : Alex van Zuiden-Rylander                                                      /
 * Class    : CSS 343 B Spring 2019 | Data Structures, Algorithms, Discrete Mathematics 2   /
 * Started  : April 2, 2019                                                                 /
 * Modified : April 2, 2019                                                                 /
 * -----------------------------------------------------------------------------------------/
 * Purpose  : This class was written in to allow the user to create polynomials. The user   /
 *            can add, subtract, multiply, compare and make deep copies of polynomials.     /
 * -----------------------------------------------------------------------------------------/
 * Notes    : This program assumes that all passed values are integers. It also assumes     /
 *            that any given input of numbers using the input stream will end in -1 -1 to   /
 *            show signal there is no more input to read.                                   /
 ------------------------------------------------------------------------------------------*/

#ifndef POLYNOMIAL_POLY_H
#define POLYNOMIAL_POLY_H

#include <iostream>

using namespace std;

typedef int Length;



class Poly {

    // Output overloading.
    friend ostream &operator<<(ostream &, const Poly &);

    // Input overloading.
    friend istream &operator>>(istream &, Poly &);

    //Private Variables.
    Length length;

    int *polyArr;
    void inline setToZero();

public:

    // Constructors.
    Poly();
    Poly(int);
    Poly(int, int);
    Poly(Poly&);
//    Poly(string&);

    // Destructor.
    ~Poly();

    // Arithmetic operators.
    Poly operator+(const Poly &rhs);
    Poly operator-(const Poly &rhs);
    Poly operator*(const Poly &rhs);
    Poly operator+=(const Poly &rhs);
    Poly operator-=(const Poly &rhs);
    Poly operator*=(const Poly &rhs);

    // Assignment operator.
    Poly operator=(const Poly &rhs);

    // Logical binary operators
    bool operator< ( const Poly & rhs ) const;
    bool operator<=( const Poly & rhs ) const;
    bool operator> ( const Poly & rhs ) const;
    bool operator>=( const Poly & rhs ) const;
    bool operator==( const Poly & rhs ) const;
    bool operator!=( const Poly & rhs ) const;

    // Mutator.
    void setCoeff(int,int);

    // Accessor.
    int getCoeff(int);

};


#endif //POLYNOMIAL_POLY_H
