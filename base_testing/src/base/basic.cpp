#include "main.h"

//Constants
const double INCH_PER_REV = 0, INCH_PER_REV_ENC = 0;
const double MAX_ACCEL = 0, MAX_VEL = 0; //units of ft and sec
double startingAngle; //accounts for any shift

//Basic Functions
void runBase(double leftPercent, double rightPercent) {

    leftBase1.move_voltage(leftPercent * 120);
    leftBase2.move_voltage(leftPercent * 120);
    rightBase1.move_voltage(rightPercent * 120);
    rightBase2.move_voltage(rightPercent * 120);

}

void runBase(double percent) {

    leftBase1.move_voltage(percent * 120);
    leftBase2.move_voltage(percent * 120);
    rightBase1.move_voltage(percent * 120);
    rightBase2.move_voltage(percent * 120);

}

double getLeftBaseEnc() {

    return (leftBase1.get_position() + leftBase2.get_position()) / 2;

}

double getRightBaseEnc() {

    return (rightBase1.get_position() + rightBase2.get_position()) / 2;

}

double getLeftBaseRPM() {

    return (leftBase1.get_actual_velocity() + leftBase2.get_actual_velocity()) / 2;

}

double getRightBaseRPM() {

    return (rightBase1.get_actual_velocity() + rightBase2.get_actual_velocity()) / 2;
        
}

bool isBaseSettled() {

    return (getLeftBaseRPM() < 5 && getRightBaseRPM() < 5);

}

void resetBaseEnc() {

    leftBase1.tare_position();
    leftBase2.tare_position();
    rightBase1.tare_position();
    leftBase2.tare_position();

}

double getLeftEnc() {

    return leftEnc.get_value();

}

double getRightEnc() {

    return rightEnc.get_value();

}

double getYawEnc() {

    return yawEnc.get_value();

}

double resetEnc() {

    leftEnc.reset();
    rightEnc.reset();
    yawEnc.reset();

}

double getAngle() {

    return gyro.get_yaw() - startingAngle;

}

//opcontrol functions
double convertJoystick(double joyVal) {

    double percentVal;

    if((double)joyVal <= -3.0) //threshold at 3/100 to prevent unwanted movement at low values
        percentVal = pow(-pow((double)joyVal, 2) - 6 * (double)joyVal + 18327.7, 0.5) - 154.414; //uses the equation of a circle to optimize slow and fast movements

    else if((double)joyVal >= 3.0) //threshold at 3/100 to prevent unwanted movement at low values
        percentVal = -pow(-pow((double)joyVal, 2) + 6 * (double)joyVal + 18327.7, 0.5) + 154.414; //uses the reflected equation to optimize slow and fast backwards movements

    else
        percentVal = 0.0;

    return percentVal;

}

void updateBase() {

    //uses joystick values to run the base
    runBase(convertJoystick(lY()), convertJoystick(rY()));

    //checks for overheating
    baseSafetyNet();

}

void baseSafetyNet() {

    //prevents the motors from overheating and breaking
    if(leftBase1.is_over_temp())
        leftBase1.set_voltage_limit(0);
    else
        leftBase1.set_voltage_limit(12000);

    if(leftBase2.is_over_temp())
        leftBase2.set_voltage_limit(0);
    else
        leftBase2.set_voltage_limit(12000);

    if(rightBase1.is_over_temp())
        rightBase1.set_voltage_limit(0);
    else
        rightBase1.set_voltage_limit(12000);

    if(rightBase2.is_over_temp())
        rightBase2.set_voltage_limit(0);
    else
        rightBase2.set_voltage_limit(12000);

}