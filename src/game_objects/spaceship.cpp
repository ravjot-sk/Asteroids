
#include "spaceship.hpp"
#include "game_constants.hpp"
#include "math.hpp"
#include "SDL2/SDL.h"
#include <array>

Spaceship::Spaceship(){     

    //Set initial position of Spaceship in middle of screen and initial rotation angle
    yPos = SCREEN_HEIGHT/2;
    xPos = SCREEN_WIDTH/2;
    angleDegrees = 0.0;
}


//Off screen detection does not take rotation into account right now

void Spaceship::moveForward(){
    
    //Calculate x and y components to move the spaceship in the direction it points
    int moveX = (int)xComponent(MOVE_VELOCITY, angleDegrees);
    int moveY = (int)yComponent(MOVE_VELOCITY,angleDegrees);

    //Move the spaceship
    xPos += moveX;
    yPos -= moveY;

    //Correct if the spaceship's x-component leaves the screen
    if(xPos<0)
        xPos = 0;
    else if(xPos +width >SCREEN_WIDTH)
        xPos = SCREEN_WIDTH-width;
    
    //Correct if the spaceship's y-component leaves the screen
    if(yPos<0)
        yPos =0;
    else if(yPos + height > SCREEN_HEIGHT)
        yPos = SCREEN_HEIGHT-height;

}

void Spaceship::moveBackward(){
    
    //Calculate x and y components to move the spaceship in the direction it points
    int moveX = (int)xComponent(MOVE_VELOCITY, angleDegrees);
    int moveY = (int)yComponent(MOVE_VELOCITY,angleDegrees);

    //Move the spaceship
    xPos -= moveX;
    yPos += moveY;

    //Correct if the spaceship's x-component leaves the screen
    if(xPos<0)
        xPos = 0;
    else if(xPos +width >SCREEN_WIDTH)
        xPos = SCREEN_WIDTH-width;
    
    //Correct if the spaceship's y-component leaves the screen
    if(yPos<0)
        yPos =0;
    else if(yPos + height > SCREEN_HEIGHT)
        yPos = SCREEN_HEIGHT-height;
        
}

void Spaceship::rotateClockwise(){
    angleDegrees+= ANGLE_VELOCITY;
}

void Spaceship::rotateCounterClockwise(){
    angleDegrees-= ANGLE_VELOCITY;
}

//Initialises a new bullet object with the position of the gun and the gun angle
void Spaceship::fireBullet(std::vector<Bullet>& bulletsOnScreen){
    //std::array<double,2> gunCoord = rotatedCoordinates(gunPosX-width/2,gunPosY-height/2,angleDegrees);
    //Initialises a new bullet object at the gun position and the direction of gun pointing
    bulletsOnScreen.emplace_back(xPos + gunPosX, yPos + gunPosY,angleDegrees);
}

int Spaceship::getXpos(){
    return xPos;
}

int Spaceship::getYpos(){
    return yPos;
}

double Spaceship::getAngle(){
    return angleDegrees;
}