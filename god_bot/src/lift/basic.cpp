#include "main.h"

// Constants
const double LEG_LENGTH = 0; // arm legnths
const double ARM_LENGTH = 0;
const double HORIZ_SHIFT = 0; // shift accounting for tower and intake placement
const double VERT_SHIFT = 0;

//Basic Functions
void runLift(double legPercent, double armPercent) {

    leftLeg.move_voltage(legPercent * 120);
    rightLeg.move_voltage(legPercent * 120);
    leftArm.move_voltage(armPercent * 120);
    rightArm.move_voltage(armPercent * 120);

}

void runLeg(double legPercent) {

    leftLeg.move_voltage(legPercent * 120);
    rightLeg.move_voltage(legPercent * 120);

}

void runArm(double armPercent) {

    leftArm.move_voltage(armPercent * 120);
    rightArm.move_voltage(armPercent * 120);

}

double getLegAngle() {

    return (leftLeg.get_position() + rightLeg.get_position()) / 2;

}

double getArmAngle() {

    return (leftArm.get_position() + rightArm.get_position()) / 2;

}

double getLegRPM() {

    return (leftLeg.get_actual_velocity() + rightLeg.get_actual_velocity()) / 2;
        
}

double getArmRPM() {

    return (leftArm.get_actual_velocity() + rightArm.get_actual_velocity()) / 2;
        
}

bool isLegSettled() {

    return (getLegRPM() < 5);

}

bool isArmSettled() {

    return (getArmRPM() < 5);

}

bool isLiftSettled() {

    return (getArmRPM() < 5 && getLegRPM() < 5);

}

void resetLiftEnc() {

    leftLeg.tare_position();
    rightLeg.tare_position();
    leftArm.tare_position();
    rightArm.tare_position();

}