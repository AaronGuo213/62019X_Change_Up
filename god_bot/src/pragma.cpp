#include "main.h"

/*====
PRAGMA
====*/

const bool isSkills = false;

Controller master (CONTROLLER_MASTER);
Controller partner (CONTROLLER_PARTNER);

Motor leftBase1(2, MOTOR_GEARSET_18, 0, E_MOTOR_ENCODER_DEGREES); 
Motor leftBase2(16, MOTOR_GEARSET_18, 0, E_MOTOR_ENCODER_DEGREES); 
Motor rightBase1(1, MOTOR_GEARSET_18, 1, E_MOTOR_ENCODER_DEGREES); 
Motor rightBase2(17, MOTOR_GEARSET_18, 1, E_MOTOR_ENCODER_DEGREES); 

Motor leftLeg(10, MOTOR_GEARSET_18, 0, E_MOTOR_ENCODER_DEGREES); 
Motor rightLeg(11, MOTOR_GEARSET_18, 1, E_MOTOR_ENCODER_DEGREES); 
Motor leftArm(10, MOTOR_GEARSET_18, 0, E_MOTOR_ENCODER_DEGREES); 
Motor rightArm(11, MOTOR_GEARSET_18, 1, E_MOTOR_ENCODER_DEGREES); 

Imu gyro(3);

ADIEncoder leftEnc(1, 2, 1);
ADIEncoder rightEnc(3, 4, 1);
ADIEncoder yawEnc(7, 8, 1);
