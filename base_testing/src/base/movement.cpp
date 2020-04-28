#include "main.h"

void moveStraight(double dist, double maxVel) {

    baseControl.disable();

}

void moveStraightVelCtrl(double dist, double maxVel, double accel, double startVel, double endVel) {

    baseControl.enable();
    double speedUpDist = (maxVel*maxVel - startVel*startVel) / (2 * accel);
    double slowDownDist = (maxVel*maxVel - endVel*endVel) / (2 * accel);
    double distLeft = dist - speedUpDist - slowDownDist;
    double coastTime;
    double currentVel = startVel;

    if(distLeft >= 0) {

        coastTime = distLeft / maxVel;
        while(currentVel < maxVel) {
            currentVel += accel * 0.05;
            baseControl.setLeftTargetVel(currentVel);
            baseControl.setRightTargetVel(currentVel);
            delay(50);
        }

        currentVel = maxVel;
        baseControl.setLeftTargetVel(maxVel);
        baseControl.setRightTargetVel(maxVel);
        for(int i = 0; i < coastTime*1000; i+= 10)
            delay(10);

        while(currentVel > endVel) {
            currentVel -= accel * 0.05;
            baseControl.setLeftTargetVel(currentVel);
            baseControl.setRightTargetVel(currentVel);
            delay(50);
        }

    }

    else {

        double topVel = sqrt(dist*accel + (startVel*startVel + endVel*endVel)/2);
        while(currentVel < topVel) {
            currentVel += accel * 0.05;
            baseControl.setLeftTargetVel(currentVel);
            baseControl.setRightTargetVel(currentVel);
            delay(50);
        }

        currentVel = topVel;

        while(currentVel > endVel) {
            currentVel -= accel * 0.05;
            baseControl.setLeftTargetVel(currentVel);
            baseControl.setRightTargetVel(currentVel);
            delay(50);
        }

    }

}