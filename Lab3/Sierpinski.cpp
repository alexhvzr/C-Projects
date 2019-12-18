//
// Created by Alex Hayden van Zuiden-Rylander on 2019-01-29.
// CSS 342 Munehiro Fukuda

#include "Sierpinski.h"
#include <iostream>
using namespace std;
int main( ) {
// right sierpinski at level 5
    Sierpinski sierp1( 120, 120, 0 );
    sierp1.rightCurve( 5, 4 );
// left sierpinski at level 5
    Sierpinski sierp2( 400, 10, 0 );
    sierp2.leftCurve( 5, 4 );
// left sierpinski at level 4
    Sierpinski sierp3( 120, 240, 0 );
    sierp3.leftCurve( 4, 8 );
// right sierpinski at level 4
    Sierpinski sierp4( 400, 130, 0 );
    sierp4.rightCurve( 4, 8 );
// right sierpinski at level 3
    Sierpinski sierp5( 120, 360, 0 );
    sierp5.rightCurve( 3, 12 );
// left sierpinski at level 3
    Sierpinski sierp6( 400, 250, 0 );
    sierp6.leftCurve( 3, 12 );
// left sierpinski at level 2
    Sierpinski sierp7( 120, 480, 0 );
    sierp7.leftCurve( 2, 16 );
// right sierpinski at level 2
    Sierpinski sierp8( 400, 370, 0 );
    sierp8.rightCurve( 2, 16 );
// right sierpinski at level 1
    Sierpinski sierp9( 120, 600, 0 );
    sierp9.rightCurve( 1, 20 );
// left sierpinski at level 1
    Sierpinski sierp10( 400, 490, 0 );
    sierp10.leftCurve( 1, 20 );
}
/*---------------------------------- Constructor ---------------------------------------------------/
 *  Uses the turtle class to implement drawing.                                                     /
 --------------------------------------------------------------------------------------------------*/
Sierpinski::Sierpinski(float initX, float initY, float initAngle) : Turtle(initX, initY, initAngle){};

/*---------------------------------- Method -------------------------------------------------------/
 *  Recursive function that draws the Sierpinski triangle arrow-head.                              /
 --------------------------------------------------------------------------------------------------*/
void Sierpinski::leftCurve(int level, float dist) {
    if(level == 0){
        draw(dist);
    }  else {
        rightCurve(level-1, dist);
        turn(60);
        leftCurve(level-1, dist);
        turn(60);
        rightCurve(level-1, dist);
    }

}

/*---------------------------------- Method -------------------------------------------------------/
 *  Recursive function that draws the Sierpinski triangle arrow-head.                               /
 --------------------------------------------------------------------------------------------------*/
void Sierpinski::rightCurve(int level, float dist) {
    if(level == 0){
        draw(dist);
    } else {
        leftCurve(level-1, dist);
        turn(-60);
        rightCurve(level-1, dist);
        turn(-60);
        leftCurve(level-1, dist);
    }


}
