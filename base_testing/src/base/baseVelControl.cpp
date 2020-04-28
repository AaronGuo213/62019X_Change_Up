#include "main.h"

BaseVelControl::BaseVelControl(PID newPID) {

    leftVelPID = newPID;
    rightVelPID = leftVelPID.clone();
    leftTargetVel = 0;
    rightTargetVel = 0;
    Task velCtrlGo(ctrlBaseVel, this, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "base motor velocity control task");

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

void runVelPIDTest() {

    FILE* file = fopen("/usd/vex/VelPIDTestData.txt", "w");
    fputs("\n\n\n\n\n", file);
    baseControl.enable();
    std::string str;
    for(int i = 0; i <= 100; i++) {
        str = "i\t" + std::to_string(getLeftBaseRPM()) + "\n";
        fputs(str.c_str(), file);
        baseControl.setLeftTargetVel(i);
        baseControl.setRightTargetVel(i);
        delay(100);
    }
    for(int i = 0; i < 10; i++) {
        str = "100\t" + std::to_string(getLeftBaseRPM()) + "\n";
        fputs(str.c_str(), file);
        delay(100);
    }
    for(int i = 100; i >= 0; i++) {
        str = "i\t" + std::to_string(getLeftBaseRPM()) + "\n";
        fputs(str.c_str(), file);
        baseControl.setLeftTargetVel(i);
        baseControl.setRightTargetVel(i);
        delay(100);
    }
    baseControl.disable();

}