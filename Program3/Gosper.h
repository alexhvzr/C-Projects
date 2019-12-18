//
// Created by Alex Hayden van Zuiden-Rylander on 2019-01-31.
//

#ifndef PROGRAM3_GOSPER_H
#define PROGRAM3_GOSPER_H

#include "Turtle.h"
#include <iostream>
#include <math.h>

class Gosper : Turtle {
public:
    Gosper(float initX = 0.0, float initY = 0.0, float initAngle = 0.0);
    void leftCurve(int level, float dist);
    void rightCurve(int level,float dist);
};

#endif //PROGRAM3_GOSPER_H
