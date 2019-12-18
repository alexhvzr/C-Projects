/*------------------------------- Program info ---------------------------------------------/
 * Author   : Alex van Zuiden-Rylander                                                      /
 * About    : This program was to practice recursion, it draws a Hexagonal Gosper Curve.    /
 * Date     : January 31, 2019                                                              /
 * Class    : CSS 342 | Data Structures, Algorithms, Discrete Mathematics                   /
 ------------------------------------------------------------------------------------------*/

#include "Gosper.h"
#include <iostream>

using namespace std;


/*---------------------------------- Constructor ---------------------------------------------------/
 *  Uses the turtle class to implement drawing.                                                     /
 --------------------------------------------------------------------------------------------------*/
Gosper::Gosper(float initX, float initY, float initAngle) : Turtle(initX, initY, initAngle) {};

/*---------------------------------- Method --------------------------------------------------------/
 *  Recursive functions that draws the left part of a Hexagonal Gosper Curve.                       /
 --------------------------------------------------------------------------------------------------*/

void Gosper::leftCurve(int level, float dist) {
    if (level == 0) {
        draw(dist);
    } else {
        leftCurve(level - 1, dist);
        turn(60);
        rightCurve(level - 1, dist);
        turn(60);
        turn(60);
        rightCurve(level - 1, dist);
        turn(-60);
        leftCurve(level - 1, dist);
        turn(-60);
        turn(-60);
        leftCurve(level - 1, dist);
        leftCurve(level - 1, dist);
        turn(-60);
        rightCurve(level - 1, dist);
        turn(60);
    }
}
/*---------------------------------- Method --------------------------------------------------------/
 *  Recursive functions that draws the right part of a Hexagonal Gosper Curve.                      /
 --------------------------------------------------------------------------------------------------*/
void Gosper::rightCurve(int level, float dist) {
    if (level == 0) {
        draw(dist);
    } else {
        turn(-60);
        leftCurve(level - 1, dist);
        turn(60);
        rightCurve(level - 1, dist);
        rightCurve(level - 1, dist);
        turn(60);
        turn(60);
        rightCurve(level - 1, dist);
        turn(60);
        leftCurve(level - 1, dist);
        turn(-60);
        turn(-60);
        leftCurve(level - 1, dist);
        turn(-60);
        rightCurve(level - 1, dist);
    }
}
