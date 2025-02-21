#ifndef GMATH_H
#define GMATH_H

#include<array>

//returns angle value in radians
double degreeToRadian(double angleDegree);

//Returns x component of a vector where angle is with respect to vertical axis
double xComponent(int magnitude, double angle);

//Returns y component of a vector where angle is with respect to vertical axis
double yComponent(int magnitude, double angle);

std::array<double,2> rotatedCoordinates(int xPos, int yPos, double angle);

std::array<double,2> rotatedGunCoordinates(int spaceshipXcenter, int spaceshipYcenter, int gunXpos, int gunYpos, double angle);

namespace CustomMath{
    int getRandomInt(int start, int end);
    double getRandomDouble(double start, double end);
}
#endif