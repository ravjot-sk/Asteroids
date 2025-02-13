#include "texture.hpp"
#include<iostream>

gameTexture::gameTexture(){

    //Initialise variables
    aTexture = NULL;
    width = 0;
    height = 0;
}

gameTexture::~gameTexture(){
    free();
}

void gameTexture::free(){
    if(aTexture!=NULL){
        SDL_DestroyTexture(aTexture);
        aTexture = NULL;
    }
    width = 0;
    height = 0;
}

int gameTexture::getHeight(){
    return height;
}

int gameTexture::getWidth(){
    return width;
}

bool gameTexture::loadTexture(std::string path,SDL_Renderer* gameRenderer){
    bool success = true;
    
    //Load image as surface
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL){
        std::cout<<"Failed to load image. SDL Error:"<<IMG_GetError();
        success = false;
        return success;
    }

    //Colour keying
    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));

    //Create texture from the surface
    SDL_Texture* newTexture = SDL_CreateTextureFromSurface(gameRenderer, loadedSurface);
    if(newTexture == NULL){
        std::cout<<"Failed to convert surface to texture. SDL Error:"<<SDL_GetError();
        success = false;
        return success;
    }
    width = loadedSurface->w;
    height = loadedSurface->h;
    
    //Free up loaded surface
    SDL_FreeSurface(loadedSurface);
    loadedSurface = NULL;
    aTexture = newTexture;
    
    return aTexture!=NULL;
}

void gameTexture::render(SDL_Renderer* gameRenderer, int x, int y, double angle, SDL_Point* center){

    //The rectangle on the screen to render
    SDL_Rect renderRect = {x,y,width,height};

    //Add to renderer
    SDL_RenderCopyEx(gameRenderer,aTexture,NULL,&renderRect,angle,center,SDL_FLIP_NONE);
}