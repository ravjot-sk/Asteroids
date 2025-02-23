#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "SDL2_ttf/SDL_ttf.h"

/* class gameTexture{
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
    

    
    //Get Image dimensions
    int getWidth();
    int getHeight();
    
};
 */
//basic Texture class
class basicTexture{
    protected:
        //actual texture
        SDL_Texture* aTexture;

        //attributes
        int width;
        int height;
    public:
        //constructor
        basicTexture();

        //destructor
        ~basicTexture();

        void free();

        //Set colour modulation
        //void setColour(Uint8 red, Uint8 green, Uint8 blue);
    
        //Set Blend Mode
        void setBlendMode(SDL_BlendMode blending = SDL_BLENDMODE_BLEND);
    
        //Set alpha modulation
        void setAlpha(Uint8 alpha);

        //renders image texture
        void render(SDL_Renderer* gameRenderer, int x, int y, double angle = 0.0, SDL_Point* center = NULL);

        //Get dimensions
        int getWidth();
        int getHeight();
};

class imgTexture : public basicTexture{
    public:
        //loads image texture
        bool loadImgTexture(std::string path, SDL_Renderer* gameRenderer);
};

class textTexture : public basicTexture{
    public:
        //creates texture from text
        bool loadTextTexture(std::string textureText, SDL_Renderer* gameRenderer, SDL_Color textColor,TTF_Font* gameFont);
};

#endif