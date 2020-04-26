#ifndef PID_H
#define PID_H

class PID {

    private:

    double kP, kI, kD, kF;
    bool useP, useI, useD, useF;
    double error, prevError, integral, derivative;


    public:

    PID(bool activeP, bool activeI, bool activeD, double P, double I, double D);
    PID(bool activeP, bool activeI, bool activeD, bool activeF, double P, double I, double D, double F);
    double calc(double setPoint, double current);
    void resetIntegral();
    PID clone();

};

#endif