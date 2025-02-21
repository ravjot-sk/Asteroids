#include "bullet.hpp"
#include "custom_math.hpp"
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
    if(xPos<-width-10 || xPos> SCREEN_WIDTH+10)
        offScreen = true;
    
    if(yPos<-height-10 || yPos > SCREEN_HEIGHT+10)
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

int Bullet::getWidth(){
    return width;
}

int Bullet::getHeight(){
    return height;
}

void Bullet::hitsTarget(){
    offScreen = true;
}