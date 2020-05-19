#include "main.h"

//Constants
const double INCH_PER_REV = 0, INCH_PER_REV_ENC = 0;
const double MAX_ACCEL = 0, MAX_VEL = 0; //units of ft and sec
double startingAngle; //accounts for any shift

//Basic Functions
void runBase(double left1Percent, double left2Percent, double right1Percent, double right2Percent) {

    leftBase1.move_voltage(left1Percent * 120);
    leftBase2.move_voltage(left2Percent * 120);
    rightBase1.move_voltage(right1Percent * 120);
    rightBase2.move_voltage(right2Percent * 120);

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
        percentVal = pow(-pow(joyVal, 2) - 6 * joyVal + 18327.7, 0.5) - 154.414; //uses the equation of a circle to optimize slow and fast movements

    else if((double)joyVal >= 3.0) //threshold at 3/100 to prevent unwanted movement at low values
        percentVal = -pow(-pow(joyVal, 2) + 6 * joyVal + 18327.7, 0.5) + 154.414; //uses the reflected equation to optimize slow and fast backwards movements

    else
        percentVal = 0.0;

    return percentVal;

}

double leftBaseRemap(double r, double theta) { //remaps the joystick value to send the correct voltage to the left base motors

    theta += 45; //shifts the angle by 45 degrees to accomodate for the angled motors on the x-drive
    float leftBaseVal;

    if(theta == 0 || theta == 180) //if the value is purely for the left base
        leftBaseVal = r;

    else if(abs(cos(theta * M_PI / 180)) >= abs(sin(theta * M_PI / 180)))
        leftBaseVal = r * sgn(cos(theta * M_PI / 180)); //makes the value equal to the x portion of the joystick vector

    else if(abs(cos(theta * M_PI / 180)) < abs(sin(theta * M_PI / 180)))
        leftBaseVal = r * cos(theta * M_PI / 180) / abs(sin(theta * M_PI / 180)); //makes the value equal to a fraction of the joystick vector

    return leftBaseVal;

}

double rightBaseRemap(double r, double theta) {//remaps the joystick value to send the correct voltage to the right base motors

    theta += 45; //shifts the angle by 45 degrees to accomodate for the angled motors on the x-drive
    float rightBaseVal;

    if(theta == 0 || theta == 180) //if the value is purely for the left base
        rightBaseVal = r;

    else if(abs(sin(theta * M_PI / 180)) >= abs(cos(theta * M_PI / 180))) 
        rightBaseVal = r * sgn(sin(theta * M_PI / 180)); //makes the value equal to the y portion of the joystick vector

    else if(abs(sin(theta * M_PI / 180)) < abs(cos(theta * M_PI / 180)))
        rightBaseVal = r * sin(theta * M_PI / 180) / abs(cos(theta * M_PI / 180)); //makes the value equal to a fraction of the joystick vector

    return rightBaseVal;

}

void updateBase() {

    double transVel = convertJoystick(sqrt(lX()*lX() + lY()*lY()));
    double rotVel = rX() * 200 / 127;
    double transAngle = atan2(lY(), lX()) - getAngle();
    double leftAveVel = leftBaseRemap(transVel, transAngle);
    double rightAveVel = rightBaseRemap(transVel, transAngle);
    baseControl.setLeftTargetVel(leftAveVel - rotVel, leftAveVel + rotVel);
    baseControl.setRightTargetVel(rightAveVel + rotVel, rightAveVel - rotVel);

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