#ifndef PID_H
#define PID_H

class PID {

    public:

    double kP, kI, kD, kF;
    bool useP, useI, useD, useF;
    double error, prevError, integral, derivative;
    
    PID(bool activeP = 0, bool activeI = 0, bool activeD = 0, double P = 0, double I = 0, double D = 0); //default constructor
    PID(bool activeP, bool activeI, bool activeD, bool activeF, double P, double I, double D, double F);
    double calc(double setPoint, double current);
    double calc(double error);
    void resetIntegral();
    PID clone();

};

#endif