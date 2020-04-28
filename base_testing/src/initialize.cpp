#include "main.h"

/*====
PRAGMA
====*/

const bool isSkills = false;

Controller master (CONTROLLER_MASTER);
Controller partner (CONTROLLER_PARTNER);

Motor leftBase1(1, MOTOR_GEARSET_18, 0, E_MOTOR_ENCODER_DEGREES); 
Motor leftBase2(2, MOTOR_GEARSET_18, 0, E_MOTOR_ENCODER_DEGREES); 
Motor rightBase1(3, MOTOR_GEARSET_18, 1, E_MOTOR_ENCODER_DEGREES); 
Motor rightBase2(4, MOTOR_GEARSET_18, 1, E_MOTOR_ENCODER_DEGREES); 

Imu gyro(5);

ADIEncoder leftEnc(1, 2, 0);
ADIEncoder rightEnc(3, 4, 0);
ADIEncoder yawEnc(5, 6, 0);


/*========
INITIALIZE
========*/

void initialize() {

    baseControl = *new BaseVelControl(*new PID(1, 1, 0, 0, 0, 0, 0, 0));
    Odometry tracker = *new Odometry(0, 0, 0);
    tracker.startTracking();

}

void disabled() {}

void competition_initialize() {}