#ifndef BASE_H
#define BASE_H

//Constants
extern const double INCH_PER_REV, INCH_PER_REV_ENC;
extern const double MAX_ACCEL, MAX_VEL; //units of ft and sec
extern const double WHEEL_DIST; //distance between sides of the base
extern double startingAngle; //accounts for any shift

//Basic Functions
void runBase(double leftPercent, double rightPercent);
void runBase(double percent);

double getLeftBaseEnc();
double getRightBaseEnc();
double getLeftBaseRPM();
double getRightBaseRPM();
bool isBaseSettled();
void resetBaseEnc();

double getLeftEnc();
double getRightEnc();
double getYawEnc();
double resetEnc();
double getAngle();

//opcontrol functions
double convertJoystick(double joyVal);
void updateBase();
void baseSafetyNet();

//odometry
class Odometry {

    private:

    double x, y, heading;
    double lastLeft, lastRight, lastYaw;
    double leftDiff, rightDiff, yawDiff;

    public:

    bool isTracking;
    Odometry(double initX, double initY, double initHeading);
    void update();
    void startTracking();
    void stopTracking();
    double getX();
    double getY();
    double getHeading();

};
void trackPos(void* param);

//velocity control
class BaseVelControl {

    private:

    double leftTargetVel, rightTargetVel;
    double leftVal, rightVal;
    PID leftVelPID, rightVelPID;

    public:

    bool isActive;
    BaseVelControl(PID newPID);
    void setLeftTargetVel(double targetVel);
    void setRightTargetVel(double targetVel);
    void disable();
    void enable();
    void update();

};
extern BaseVelControl baseControl; //in initialize
void ctrlBaseVel(void* param);
void runVelPIDTest();

//base movement functions
void moveStraight(double dist, double maxVel = 100);
void moveStraightVelCtrl(double dist, double maxVel = 100);
void moveStraightMP(double dist, double maxVel = MAX_VEL, double accel = MAX_ACCEL, double startVel = 0, double endVel = 0);
void moveCircular(double radius, bool clockwise, double centerVel);

#endif