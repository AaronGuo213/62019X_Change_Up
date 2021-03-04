#include "main.h"

Odometry::Odometry(double initX, double initY, double initHeading) {

    x = initX;
    y = initY;
    heading = initHeading;
    lastLeft = getLeftEnc();
    lastRight = getRightEnc();
    lastYaw = getYawEnc();
    lastHeading = 0; // do not use getAngle(), it destroys the code
    isTracking = false;
    YAW_ENC_DIST = 8.5;

}

void Odometry::update() {

    // looping heading
    if(getAngle() > 170 && lastHeading < -170) {
        lastHeading += 360;
    }
    else if(getAngle() < -170 && lastHeading > 170) {
        lastHeading -= 360;
    }

    leftDiff = getLeftEnc() - lastLeft;
    rightDiff = getRightEnc() - lastRight;
    yawDiff = getYawEnc() - lastYaw;
    headingDiff = getAngle() - lastHeading;
    realYawDiff = yawDiff - (YAW_ENC_DIST * (-headingDiff * M_PI / 180));

    lastLeft = getLeftEnc();
    lastRight = getRightEnc();
    lastYaw = getYawEnc();
    lastHeading = getAngle();

    x += cos(heading * M_PI / 180) * (leftDiff + rightDiff) / 2; // forwards displacement
    x += sin(heading * M_PI / 180) * realYawDiff; // horizontal displacement
    y += sin(heading * M_PI / 180) * (leftDiff + rightDiff) / 2; // forwards displacement
    y += cos(heading * M_PI / 180) * realYawDiff; // horizontal displacement
    heading += headingDiff;

}

void Odometry::startTracking() {

    isTracking = true;
    void* package = static_cast<void*>(this);
    Task trackingGo(trackPos, package, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "position tracking task");

}

void Odometry::stopTracking() {

    isTracking = false;

}

double Odometry::getX() {

    return x;

}

double Odometry::getY() {

    return y;

}

double Odometry::getHeading() {

    return heading;

}

void trackPos(void* param) {

    std::uint32_t now = millis();
    Odometry* odom = static_cast<Odometry*>(param);
    while(odom->isTracking) {
        odom->update();
        Task::delay_until(&now, 50);
    }

}