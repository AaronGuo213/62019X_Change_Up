#include "main.h"

BaseVelControl::BaseVelControl(PID newPID) {

    leftVelPID = newPID;
    rightVelPID = leftVelPID.clone();
    leftTargetVel = 0;
    rightTargetVel = 0;

}

void BaseVelControl::setLeftTargetVel(double targetVel) {

    leftTargetVel = targetVel;

}

void BaseVelControl::setRightTargetVel(double targetVel) {

    rightTargetVel = targetVel;

}

void BaseVelControl::disable() {

    isActive = false;

}

void BaseVelControl::enable() {

    isActive = true;

}

void BaseVelControl::update() {

    leftVal = leftVelPID.calc(leftTargetVel, getLeftBaseRPM());
    rightVal = rightVelPID.calc(rightTargetVel, getRightBaseRPM());
    runBase(leftVal, rightVal);

}

void ctrlBaseVel(void* param) {

    std::uint32_t now = millis();
    BaseVelControl system = *static_cast<BaseVelControl*>(param);
    while(true) {
        if(system.isActive)
            system.update();
            
        Task::delay_until(&now, 50);
    }

}