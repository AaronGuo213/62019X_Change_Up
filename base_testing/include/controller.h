#ifndef CONTROLLER_H
#define CONTROLLER_H

int sgn(double x);

double lY(Controller cont = master);
double lX(Controller cont = master);
double rY(Controller cont = master);
double rX(Controller cont = master);
bool l1Pressed(Controller cont = master, bool newPress = false);
bool l2Pressed(Controller cont = master, bool newPress = false);
bool r1Pressed(Controller cont = master, bool newPress = false);
bool r2Pressed(Controller cont = master, bool newPress = false);
bool upPressed(Controller cont = master, bool newPress = false);
bool downPressed(Controller cont = master, bool newPress = false);
bool leftPressed(Controller cont = master, bool newPress = false);
bool rightPressed(Controller cont = master, bool newPress = false);
bool aPressed(Controller cont = master, bool newPress = false);
bool bPressed(Controller cont = master, bool newPress = false);
bool xPressed(Controller cont = master, bool newPress = false);
bool yPressed(Controller cont = master, bool newPress = false);

#endif