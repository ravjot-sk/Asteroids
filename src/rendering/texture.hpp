#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"

class gameTexture{
    private:
    //actual hardware texture
    SDL_Texture* aTexture;
    
    //Image dimensions
    int width;
    int height;

public:
    gameTexture();
    
    //Deallocates Memory
    ~gameTexture();
    
    //Load image from specfied path
    bool loadTexture(std::string path, SDL_Renderer* gameRenderer);
    
    //Deallocates Texture
    void free();
    
    //Render Texture at given point
    void render(SDL_Renderer* gameRenderer, int x, int y, double angle = 0.0, SDL_Point* center = NULL);
    
    //Set colour modulation
    //void setColour(Uint8 red, Uint8 green, Uint8 blue);
    
    //Set Blend Mode
    //void setBlendMode(SDL_BlendMode blending);
    
    //Set alpha modulation
    //void setAlpha(Uint8 alpha);
    
    //Get Image dimensions
    int getWidth();
    int getHeight();
    
};

#endif