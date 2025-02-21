#ifndef COLLISION_H
#define COLLISION_H

#include "SDL2/SDL.h"

bool areRectanglesColliding(SDL_Rect* rectangle1, SDL_Rect* rectangle2, double angle1=0.0,double angle2=0.0);
#endif