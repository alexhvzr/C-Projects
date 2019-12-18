//
// Created by Alex Hayden van Zuiden-Rylander on 2019-01-29.
//

#ifndef LAB3_SIERPINSKI_H
#define LAB3_SIERPINSKI_H
#include "Turtle.h"
#include <iostream>
#include <math.h>
using namespace std;
//------------------------------------------------------------------------

// Sierpinski curve:
//   -- leftCurve: draws a left sierpinski arrowhead at a given level
//   -- rightCurve: draws a right sierpinski arrowhead at a given level
//
// Assumptions:
//   -- Level l is defined as an integer.
//   -- Distance d is define as a float.
//   -- Outputs are in postscript format.
//------------------------------------------------------------------------

class Sierpinski : Turtle {
public:
    Sierpinski( float initX=0.0, float initY=0.0, float initAngle=0.0 );
    void leftCurve( int level, float dist );  //draw a level-l left curve with dist d
    void rightCurve( int level, float dist ); //draw a level-l right curve with dist d
};

#endif //LAB3_SIERPINSKI_H
