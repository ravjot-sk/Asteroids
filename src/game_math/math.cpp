#include "math.hpp"
#include <cmath>

double degreeToRadian(double angleDegree){
    return M_PI * angleDegree/180;
}

double xComponent(int magnitude, double angle){

    return magnitude * sin(degreeToRadian(angle));
}

double yComponent(int magnitude, double angle){
    return magnitude* cos(degreeToRadian(angle));
}

std::array<double,2> rotatedCoordinates(int xPos, int yPos, double angle){
    double newXpos = xPos * cos(degreeToRadian(angle)) - yPos * sin(degreeToRadian(angle));
    double newYpos = yPos * cos(degreeToRadian(angle)) + xPos * sin(degreeToRadian(angle));
    std::array<double,2> newCoord ={newXpos,newYpos};

    return newCoord;
}

std::array<double,2> rotatedGunCoordinates(int spaceshipXcenter, int spaceshipYcenter, int gunXpos, int gunYpos, double angle){
    std::array<double,2> rotatedRelative = rotatedCoordinates(gunXpos-spaceshipXcenter,gunYpos-spaceshipYcenter,angle);
    rotatedRelative[0] += spaceshipXcenter;
    rotatedRelative[1] += spaceshipYcenter;
    
    return rotatedRelative;
}