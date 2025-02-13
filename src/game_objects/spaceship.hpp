#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <vector>
#include "bullet.hpp"

class Spaceship{
    private:
        int xPos,yPos;
        double angleDegrees;

        //Spaceship Dimensions set based on the image used
        static const int height = 100;
        static const int width = 78;

        //Gun Position based on image used
        static const int gunPosX = 73;
        static const int gunPosY = 83;

        //Sets the minimum move increments
        static constexpr int MOVE_VELOCITY = 5;
        static constexpr double ANGLE_VELOCITY = 5.0;
    public:
        //Initialises variables
        Spaceship();

        //Moving the spaceship
        void moveForward();
        void moveBackward();
        void rotateCounterClockwise();
        void rotateClockwise();

        //Fires a bullet
        void fireBullet(std::vector<Bullet>& bulletsOnScreen);

        //Returns the current spaceship position and angle
        int getXpos();
        int getYpos();
        double getAngle();
};

#endif