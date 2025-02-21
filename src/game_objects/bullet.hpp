#ifndef BULLET_H
#define BULLET_H

#include "SDL2/SDL.h"

class Bullet{
    private:
        //Bullet dimensions set based on image used
        static const int height = 50;
        static const int width = 41;

        //Rel coordinates of spaceship center from Bullet origin. Will be needed to rotate the bullet along with the spaceship
        static const int rotationCenterX =-34;
        static const int rotationCenterY =-33;

        //Position on screen
        int xPos,yPos;

        //Orientation of appearance
        double angleDegrees;

        //Firing angle
        double firingAngle;

        //Flag to check off screen
        bool offScreen;

        //Bullet moving speed
        const static int BULLET_VELOCITY = 10;

    
    public:
        //Initialise bullet characteristics
        Bullet(int x, int y, double ang);

        //Move the bullet the distance based on how much time
        void move(int timeElapsed=1);

        //Returns the off screen flag
        bool isOffScreen();

        //Returns the current bullet position and angle and center
        int getXpos();
        int getYpos();
        double getAngle();
        int getCenterX();
        int getCenterY();
        int getWidth();
        int getHeight();

        //When target hit, set to offscreen
        void hitsTarget();
};


#endif