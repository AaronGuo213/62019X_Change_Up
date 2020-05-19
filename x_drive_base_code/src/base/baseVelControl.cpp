#include "main.h"

BaseVelControl::BaseVelControl(PID newPID) {

    left1VelPID = newPID;
    left2VelPID = left1VelPID.clone();
    right1VelPID = left1VelPID.clone();
    right2VelPID = left1VelPID.clone();
    left1TargetVel = 0;
    left2TargetVel = 0;
    right1TargetVel = 0;
    right2TargetVel = 0;
    Task velCtrlGo(ctrlBaseVel, this, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "base motor velocity control task");

}

void BaseVelControl::setLeftTargetVel(double frontTargetVel, double backTargetVel) {

    left1TargetVel = frontTargetVel;
    left2TargetVel = backTargetVel;

}

void BaseVelControl::setRightTargetVel(double frontTargetVel, double backTargetVel) {

    right1TargetVel = frontTargetVel;
    right1TargetVel = backTargetVel;

}

void BaseVelControl::disable() {

    isActive = false;

}

void BaseVelControl::enable() {

    isActive = true;

}

void BaseVelControl::update() {

    left1Val = left1VelPID.calc(left1TargetVel, getLeftBaseRPM());
    right1Val = right1VelPID.calc(right1TargetVel, getRightBaseRPM());
    runBase(left1Val, left2Val, right1Val, right2Val);

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