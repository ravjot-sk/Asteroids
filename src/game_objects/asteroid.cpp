#include "asteroid.hpp"
#include "custom_math.hpp"
#include "game_constants.hpp"

//angles are measured from vertical. positive is clockwise direction

Asteroid::Asteroid(int h, int w){

    height = h;
    width = w;

    offScreen = false;

    rotationSpeed = CustomMath::getRandomInt(3,8);
    angle = 0.0;
    //Start the asteroid from the 4 edges of the screen randomly
    switch (CustomMath::getRandomInt(1,4))
    {
        //Top of the screen
    case 1:
        yPos = 0;
        
        //Set x position with some padding
        xPos = CustomMath::getRandomInt(width,SCREEN_WIDTH-width);

        //Should move below from the edge
        angleMovement = CustomMath::getRandomDouble(110.0, 250.0);

        break;
    
    //Right edge of screen
    case 2:
        xPos = SCREEN_WIDTH;

        //Set y position with some padding
        yPos = CustomMath::getRandomInt(height, SCREEN_HEIGHT-height);

        //Angle of movement should be towards left
        angleMovement = CustomMath::getRandomDouble(200.0,340.0);
        break;

    //Bottom of the screen
    case 3:
        yPos = SCREEN_HEIGHT;

        //Set x position with some padding
        xPos = CustomMath::getRandomInt(width,SCREEN_WIDTH-width);

        //Angle of movement should be towards the top
        angleMovement = CustomMath::getRandomDouble(-70.0, 70.0);
        break;
    
    //Left edge of the screen
    case 4:
        xPos = 0;
        
        //Set y position with some padding
        yPos = CustomMath::getRandomInt(height, SCREEN_HEIGHT-height);

        //Angle of movement should be towards the right
        angleMovement = CustomMath::getRandomDouble(20.0,160.0);
        break;
    }

    //Set speed of the asteroid
    speed = CustomMath::getRandomInt(2,7);
}

bool Asteroid::isOffScreen(){
    return offScreen;
}

int Asteroid::getXpos(){
    return xPos;
}
int Asteroid::getYpos(){
    return yPos;
}

int Asteroid::getWidth(){
    return width;
}

int Asteroid::getHeight(){
    return height;
}

void Asteroid::move(int timeElapsed){

    //Move the asteroid in x and y direction
    xPos+= (int) xComponent(speed*timeElapsed,angleMovement);
    yPos-= (int) yComponent(speed*timeElapsed,angleMovement);

    //Check if bullet is off screen
    if(xPos<-width-10 || xPos> SCREEN_WIDTH+10)
        offScreen = true;

    if(yPos<-height-10 || yPos > SCREEN_HEIGHT +10)
        offScreen = true;
}

void Asteroid::rotate(){
    angle+=rotationSpeed;
}

double Asteroid::getAngle(){
    return angle;
}

void Asteroid::gotHit(){
    offScreen = true;
}

double Asteroid::getAngleMovement(){
    return angleMovement;
}

void Asteroid::updateAngleMovement(double newAngle){
    angleMovement = newAngle;
}