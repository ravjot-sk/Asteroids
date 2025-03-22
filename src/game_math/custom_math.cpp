#include "custom_math.hpp"
#include <cmath>
#include <random>

double degreeToRadian(double angleDegree){
    return M_PI * angleDegree/180;
}

//Angle is measured from the vertical. Positive is clockwise direction. 
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

namespace CustomMath{
    //Might cause performance issues
    int getRandomInt(int start, int end){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(start,end);
    return dist(gen);
    }

    double getRandomDouble(double start, double end){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dist(start, end);
        return dist(gen);
    }
}

double newAngleAfterCollision(std::pair<int,int> center1, std::pair<int,int> center2, double angleVelocity1){
    double x = center2.first - center1.first;
    double y = center2.second - center1.second;

    //atan returns angle in radians
    double theta = atan(x/y)*180.0/3.1415;
    return 180-angleVelocity1-2*theta;
}