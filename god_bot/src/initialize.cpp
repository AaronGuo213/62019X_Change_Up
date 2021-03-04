#include "main.h"

/*========
INITIALIZE
========*/

void initialize() {

    delay(2500);
    //baseControl = *new BaseVelControl(*new PID(1, 1, 0, 0, 0, 0, 0, 0));
    startingAngle = gyro.get_yaw();
    tracker = *new Odometry(0, 0, 0);
    tracker.startTracking();

}

void disabled() {}

void competition_initialize() {}