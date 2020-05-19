#include "main.h"

PID::PID(bool activeP, bool activeI, bool activeD, double P, double I, double D) {
    useP = activeP;
    useI = activeI;
    useD = activeD;
    useF = false;
    kP = P;
    kI = I;
    kD = D;
    kF = 0;
    error = prevError = integral = derivative = 0;
}

PID::PID(bool activeP, bool activeI, bool activeD, bool activeF, double P, double I, double D, double F) {
    useP = activeP;
    useI = activeI;
    useD = activeD;
    useF = false;
    kP = P;
    kI = I;
    kD = D;
    kF = F;
    error = prevError = integral = derivative = 0;
}

double PID::calc(double setPoint, double current) {

    error = setPoint - current;
    integral += error;
    derivative = error - prevError;
    prevError = error;
    return ((double)useF * kF * setPoint) + ((double)useP * kP * error) + ((double)useI * kI * integral) + ((double)useD * kD * derivative);

}

void PID::resetIntegral() {

    integral = 0;

}

PID PID::clone() {

    return *(new PID(useP, useI, useD, useF, kP, kI, kD, kF));

}