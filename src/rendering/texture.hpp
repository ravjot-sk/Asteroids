#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "SDL2_ttf/SDL_ttf.h"

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

         // Prevent copying
    basicTexture(const basicTexture&) = delete;
    basicTexture& operator=(const basicTexture&) = delete;

    // Allow move semantics
    basicTexture(basicTexture&& other) noexcept;
    basicTexture& operator=(basicTexture&& other) noexcept;

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