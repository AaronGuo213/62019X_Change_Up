#include "main.h"

double getLiftX() {

    double legComp = cos(getLegAngle()*3.14159/180) * LEG_LENGTH;
    double armComp = cos(getArmAngle()*3.14159/180) * ARM_LENGTH;
    return legComp + armComp + HORIZ_SHIFT;

}

double getLiftY() {

    double legComp = sin(getLegAngle()*3.14159/180) * LEG_LENGTH;
    double armComp = sin(getArmAngle()*3.14159/180) * ARM_LENGTH;
    return legComp + armComp + VERT_SHIFT;

}