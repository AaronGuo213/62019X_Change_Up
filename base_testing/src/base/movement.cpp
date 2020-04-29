#include "main.h"

void moveStraight(double distance, double maxVal) { 
    //PID control loop to move the base to a certain relative 
    //postition with minimal forwards and sideways error

    baseControl.disable();
    resetBaseEnc();
    double distVal, diffVal, leftVal, rightVal; //power values for the motors
    double leftStart = getLeftEnc(), rightStart = getRightEnc(); //marks the staring spot
    double leftDist, rightDist; //variables for position
    double startAngle = getAngle();
    PID dist = *new PID(1, 1, 1, 9, 0.004, 10); //kP = 9, kI = 0.004, kD = 10
    PID diff = *new PID(1, 0, 0, 5, 0, 0); //kP = 5

    for(int i = 0; true; i+=10) {

        //updates current distance, PID errors, and motor values
        leftDist = getLeftBaseEnc() - leftStart;
        rightDist = getRightBaseEnc() - rightStart;

        distVal = dist.calc(distance, (leftDist + rightDist) / 2);
        diffVal = diff.calc((getLeftBaseEnc() - getRightBaseEnc()) / 2);
        
        //limits the influence of the diffVal when near the setpoint
        diffVal = abs(dist.error) < 4 ? diffVal * 0.1 : diffVal;
        //limits the values before sending them to the motors
        distVal = abs(distVal) > abs(maxVal) ? maxVal * sgn(distVal) : distVal;
        leftVal = distVal - diffVal;
        rightVal = distVal + diffVal;
        runBase(leftVal, rightVal);

        //stops when threshhold is reached and speed is slow enough or robot stops
        if(i > 200 && isBaseSettled())
            break;

        //debugging
        std::cout << "setPoint: " << distance << " | pos: " << (leftDist + rightDist) / 2 << " | error: " << dist.error << " | distVal: " << distVal << " | diff error: " << diff.error <<  " | diffVal: " << diffVal << " | time: " << i << "\n";

        delay(50);

    }

    runBase(0, 0); //stops the motors

}

void moveStraightVelCtrl(double distance, double maxVal) { 
    //PID control loop to move the base to a certain relative 
    //postition with minimal forwards and sideways error

    baseControl.enable();
    resetBaseEnc();
    double distVal, lastVal; //power values for the motors
    double leftStart = getLeftEnc(), rightStart = getRightEnc(); //marks the staring spot
    double leftDist, rightDist; //variables for position
    double startAngle = getAngle();
    PID dist = *new PID(1, 1, 1, 9, 0.004, 10); //kP = 9, kI = 0.004, kD = 10

    for(int i = 0; true; i+=10) {

        //updates current distance, PID errors, and motor values
        leftDist = getLeftBaseEnc() - leftStart;
        rightDist = getRightBaseEnc() - rightStart;

        distVal = dist.calc(distance, (leftDist + rightDist) / 2);
        distVal = abs(distVal) > abs(maxVal) ? maxVal * sgn(distVal) : distVal;
        runBase(distVal, distVal);

        //stops when threshhold is reached and speed is slow enough or robot stops
        if(i > 200 && isBaseSettled())
            break;

        //debugging
        std::cout << "setPoint: " << distance << " | pos: " << (leftDist + rightDist) / 2 << " | error: " << dist.error << " | distVal: " << distVal << " | time: " << i << "\n";

        delay(50);

    }

    runBase(0, 0); //stops the motors

}

void moveStraightMP(double dist, double maxVel, double accel, double startVel, double endVel) {

    baseControl.enable();
    double speedUpDist = (maxVel*maxVel - startVel*startVel) / (2 * accel); //dist needed to speed up
    double slowDownDist = (maxVel*maxVel - endVel*endVel) / (2 * accel); //dist needed to slow down
    double distLeft = dist - speedUpDist - slowDownDist; //available dist left for coasting at max speed
    double coastTime;
    double currentVel = startVel;

    if(distLeft >= 0) { //robot can accelerate to max speed then decelerate

        coastTime = distLeft / maxVel; //extra time to move at max speed
        while(currentVel < maxVel) { //accelerating
            currentVel += accel * 0.05;
            baseControl.setLeftTargetVel(currentVel);
            baseControl.setRightTargetVel(currentVel);
            delay(50);
        }

        currentVel = maxVel;
        baseControl.setLeftTargetVel(maxVel); //coasting at max speed
        baseControl.setRightTargetVel(maxVel);
        for(int i = 0; i < coastTime*1000; i+= 10)
            delay(10);

        while(currentVel > endVel) { //decelerating
            currentVel -= accel * 0.05;
            baseControl.setLeftTargetVel(currentVel);
            baseControl.setRightTargetVel(currentVel);
            delay(50);
        }

    }

    else { //robot does not have enough distance to accel to max velocity and decel to end vel

        double topVel = sqrt(dist*accel + (startVel*startVel + endVel*endVel)/2); //finds max reachable vel
        while(currentVel < topVel) { //accelerates
            currentVel += accel * 0.05;
            baseControl.setLeftTargetVel(currentVel);
            baseControl.setRightTargetVel(currentVel);
            delay(50);
        }

        currentVel = topVel;

        while(currentVel > endVel) { //decelerates
            currentVel -= accel * 0.05;
            baseControl.setLeftTargetVel(currentVel);
            baseControl.setRightTargetVel(currentVel);
            delay(50);
        }

    }

}

void moveCircular(double radius, bool clockwise, double centerVel) { //clockwise and sign of center vel determine direction

    double leftVel, rightVel;
    
    if(clockwise ^ (centerVel > 0)) { //clockwise & negative or ccw & positive means left is slower
        leftVel = centerVel * (radius-WHEEL_DIST/2)/radius;
        rightVel = centerVel * (radius+WHEEL_DIST/2)/radius;
    }
    else {
        leftVel = centerVel * (radius+WHEEL_DIST/2)/radius;
        rightVel = centerVel * (radius-WHEEL_DIST/2)/radius;
    }
    baseControl.setLeftTargetVel(leftVel);
    baseControl.setRightTargetVel(rightVel);

}