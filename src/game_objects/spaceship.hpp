#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <list>
#include "bullet.hpp"

class Spaceship{
    private:
        int xPos,yPos;
        double angleDegrees;

        //Spaceship Dimensions set based on the image used
        static int height;
        static int width;

        //Gun Position based on image used
        static int gunPosX;
        static int gunPosY;

        //Sets the minimum move increments
        static constexpr int MOVE_VELOCITY = 5;
        static constexpr double ANGLE_VELOCITY = 5.0;
    public:
        //Initialises variables
        Spaceship();

        static void initialise(int h = 100, int w = 78, int gunX = 73, int gunY = 83);

        //Moving the spaceship
        void moveForward();
        void moveBackward();
        void rotateCounterClockwise();
        void rotateClockwise();

        //Fires a bullet
        void fireBullet(std::list<Bullet>& bulletsOnScreen);

        //Returns the current spaceship position and angle
        int getXpos();
        int getYpos();
        double getAngle();
        int getWidth();
        int getHeight();
};

#endif