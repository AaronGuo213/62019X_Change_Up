#include "main.h"

Odometry::Odometry(double initX, double initY, double initHeading) {

    x = initX;
    y = initY;
    heading = initHeading;

}

void Odometry::update() {

    leftDiff = getLeftEnc() - lastLeft;
    rightDiff = getRightEnc() - lastRight;
    yawDiff = getYawEnc() - lastYaw;
    lastLeft = getLeftEnc();
    lastRight = getRightEnc();
    lastYaw = getYawEnc();
    heading = getAngle();
    x += cos(heading * M_PI / 180) * (leftDiff + rightDiff) / 2;
    y += sin(heading * M_PI / 180) * (leftDiff + rightDiff) / 2;

}

void Odometry::startTracking() {

    isTracking = true;
    Odometry* tracker = this;
    Task trackingGo(trackPos, tracker, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "position tracking task");

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
    Odometry odom = *static_cast<Odometry*>(param);
    while(odom.isTracking) {
        odom.update();
        Task::delay_until(&now, 50);
    }

}