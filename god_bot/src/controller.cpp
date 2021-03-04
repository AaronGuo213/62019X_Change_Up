#include "main.h"

int sgn(double x) {

    return (x > 0) - (x < 0);

}

double lY(Controller cont) {
    return cont.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
}

double lX(Controller cont) {
    return cont.get_analog(E_CONTROLLER_ANALOG_LEFT_X);
}

double rY(Controller cont) {
    return cont.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
}

double rX(Controller cont) {
    return cont.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);
}

bool l1Pressed(Controller cont, bool newPress) {
    if(!newPress)
        return cont.get_digital(E_CONTROLLER_DIGITAL_L1);
    return cont.get_digital_new_press(E_CONTROLLER_DIGITAL_L1);
}

bool l2Pressed(Controller cont, bool newPress) {
    if(!newPress)
        return cont.get_digital(E_CONTROLLER_DIGITAL_L2);
    return cont.get_digital_new_press(E_CONTROLLER_DIGITAL_L2);
}

bool r1Pressed(Controller cont, bool newPress) {
    if(!newPress)
        return cont.get_digital(E_CONTROLLER_DIGITAL_R1);
    return cont.get_digital_new_press(E_CONTROLLER_DIGITAL_R1);
}

bool r2Pressed(Controller cont, bool newPress) {
    if(!newPress)
        return cont.get_digital(E_CONTROLLER_DIGITAL_R2);
    return cont.get_digital_new_press(E_CONTROLLER_DIGITAL_R2);
}

bool upPressed(Controller cont, bool newPress) {
    if(!newPress)
        return cont.get_digital(E_CONTROLLER_DIGITAL_UP);
    return cont.get_digital_new_press(E_CONTROLLER_DIGITAL_UP);
}

bool downPressed(Controller cont, bool newPress) {
    if(!newPress)
        return cont.get_digital(E_CONTROLLER_DIGITAL_DOWN);
    return cont.get_digital_new_press(E_CONTROLLER_DIGITAL_DOWN);
}

bool leftPressed(Controller cont, bool newPress) {
    if(!newPress)
        return cont.get_digital(E_CONTROLLER_DIGITAL_LEFT);
    return cont.get_digital_new_press(E_CONTROLLER_DIGITAL_LEFT);
}

bool rightPressed(Controller cont, bool newPress) {
    if(!newPress)
        return cont.get_digital(E_CONTROLLER_DIGITAL_RIGHT);
    return cont.get_digital_new_press(E_CONTROLLER_DIGITAL_RIGHT);
}

bool aPressed(Controller cont, bool newPress) {
    if(!newPress)
        return cont.get_digital(E_CONTROLLER_DIGITAL_A);
    return cont.get_digital_new_press(E_CONTROLLER_DIGITAL_A);
}

bool bPressed(Controller cont, bool newPress) {
    if(!newPress)
        return cont.get_digital(E_CONTROLLER_DIGITAL_B);
    return cont.get_digital_new_press(E_CONTROLLER_DIGITAL_B);
}

bool xPressed(Controller cont, bool newPress) {
    if(!newPress)
        return cont.get_digital(E_CONTROLLER_DIGITAL_X);
    return cont.get_digital_new_press(E_CONTROLLER_DIGITAL_X);
}

bool yPressed(Controller cont, bool newPress) {
    if(!newPress)
        return cont.get_digital(E_CONTROLLER_DIGITAL_Y);
    return cont.get_digital_new_press(E_CONTROLLER_DIGITAL_Y);
}