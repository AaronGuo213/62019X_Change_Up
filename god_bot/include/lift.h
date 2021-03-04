#ifndef LIFT_H
#define LIFT_H

// Constants
extern const double LEG_LENGTH; // arm legnths
extern const double ARM_LENGTH;
extern const double HORIZ_SHIFT; // shift accounting for tower and intake placement
extern const double VERT_SHIFT;

// Basic Functions
void runLift(double legPercent, double armPercent);
void runLeg(double legPercent);
void runArm(double armPercent);
double getLegAngle();
double getArmAngle();
double getLegRPM();
double getArmRPM();
bool isLegSettled();
bool isArmSettled();
bool isLiftSettled();
void resetLiftEnc();

// Point Follower Functions
double getLiftX();

#endif