#include "texture.hpp"
#include<iostream>

/* gameTexture::gameTexture(){

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
 */
//constructor to initialise members
basicTexture::basicTexture(){
    //Initialise variables
    aTexture = NULL;
    width = 0;
    height = 0;
}

//destructor calls the free method
basicTexture::~basicTexture(){
    free();
}

//destroy texture and set attributes to 0
void basicTexture::free(){
    if(aTexture!=NULL){
        SDL_DestroyTexture(aTexture);
        aTexture = NULL;
    }
    width = 0;
    height = 0;
}

//sets the blending mode for the texture
void basicTexture::setBlendMode(SDL_BlendMode blending){
    SDL_SetTextureBlendMode(aTexture,blending);
}

//sets the alpha blending
void basicTexture::setAlpha(Uint8 alpha){
    SDL_SetTextureAlphaMod(aTexture,alpha);
}

//actual rendering on the screen
void basicTexture::render(SDL_Renderer* gameRenderer, int x, int y, double angle, SDL_Point* center){

    //The rectangle on the screen to render
    SDL_Rect renderRect = {x,y,width,height};

    //Add to renderer
    SDL_RenderCopyEx(gameRenderer,aTexture,NULL,&renderRect,angle,center,SDL_FLIP_NONE);
}

//return width
int basicTexture::getWidth(){
    return width;
}

//return height
int basicTexture::getHeight(){
    return height;
}

bool imgTexture::loadImgTexture(std::string path, SDL_Renderer* gameRenderer){
    bool success = true;
    
    //Load image as surface
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL){
        std::cout<<"Failed to load image. SDL Error:"<<IMG_GetError();
        success = false;
        return success;
    }

    //Colour keying set to white 
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

bool textTexture::loadTextTexture(std::string textureText, SDL_Renderer* gameRenderer, SDL_Color textColor,TTF_Font* gameFont){
    bool success = true;
    SDL_Surface* textSurface = TTF_RenderText_Solid(gameFont,textureText.c_str(),textColor);
    if(textSurface == NULL){
        std::cout<<"Unable to render text surface! SDL_ttf Error:"<<TTF_GetError()<<std::endl;
        success = false;
        return success;
    }
    //Create a texture from the surface
    aTexture = SDL_CreateTextureFromSurface(gameRenderer,textSurface);
    if(aTexture == NULL){
        std::cout<<"Failed to create texture from text surface! SDL Error: "<<SDL_GetError()<<std::endl;
        success = false;
        return success;
    }

    //set dimensions
    width = textSurface->w;
    height = textSurface->h;

    SDL_FreeSurface(textSurface);

    return aTexture!=NULL;
}