#ifndef ASTEROID_H
#define ASTEROID_H


class Asteroid{
    private:
    //Asteroid dimensions
    static const int height = 200;
    static const int width = 177;

    //Asteroid rotation speed
    int rotationSpeed;
    double angle;

    //Asteroid position on screen
    int xPos;
    int yPos;

    //Asteroid direction of movement
    double angleMovement;
    double speed;

    bool offScreen;

    public:
    // Constructor initialises screen edge where the asteroid originates and sets the direction and velocity of travel randomly 
    Asteroid();

    //Check if bullet is off screen
    bool isOffScreen();

    //Moving the asteroid
    void move(int timeElapsed=1);

    //Rotate the asteroid
    void rotate();

    //Returns the current position 
    int getXpos();
    int getYpos();
    double getAngle();

};

#endif