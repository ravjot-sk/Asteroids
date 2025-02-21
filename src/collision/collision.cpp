#include "collision.hpp"

//Basic collision detection without angles
bool areRectanglesColliding(SDL_Rect* rectangle1,SDL_Rect* rectangle2, double angle1, double angle2){
    return SDL_HasIntersection(rectangle1,rectangle2);
}