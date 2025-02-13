#include "bullet.hpp"
#include "math.hpp"
#include "game_constants.hpp"

Bullet::Bullet(int x, int y, double ang){

    //Set bullet start position
    xPos = x;
    yPos = y;

    //Set bullet orientation angle
    angleDegrees = ang;

    //Set bullet firing angle
    firingAngle = ang+30+90;

    // Bullet should be initially on screen
    offScreen = false;
}

void Bullet::move(int timeElapsed){

    //Move bullet in x and y directions
    xPos += (int) xComponent(BULLET_VELOCITY*timeElapsed,firingAngle);

    yPos -= (int) yComponent(BULLET_VELOCITY*timeElapsed,firingAngle);

    //Check if bullet is off screen
    if(xPos<0 || xPos> SCREEN_WIDTH)
        offScreen = true;
    
    if(yPos<0 || yPos > SCREEN_HEIGHT)
        offScreen = true;
}


bool Bullet::isOffScreen(){
    return offScreen;
}

int Bullet::getXpos(){
    return xPos;
}

int Bullet::getYpos(){
    return yPos;
}

double Bullet::getAngle(){
    return angleDegrees;
}

int Bullet::getCenterX(){
    return rotationCenterX;
}
int Bullet::getCenterY(){
    return rotationCenterY;
}