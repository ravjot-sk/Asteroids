#include "initialising.hpp"
#include "timer.hpp"
#include <iostream>

int main(int argc, char* args[]){
    SDL_Window* gameWindow = NULL;
    SDL_Renderer* gameRenderer = NULL;

    if( ! init(&gameWindow, &gameRenderer)){
        std::cout<<"Initialisation failed!\n";
        return EXIT_FAILURE;
    }
    if(gameWindow==NULL){
        std::cout<<"\n Window still NULL \n";
        return EXIT_FAILURE;
    }
    Spaceship ship;
    gameTexture spaceshipTexture;

    gameTexture bulletTexture;

    if (!loadSpaceshipTexture(gameRenderer,spaceshipTexture)){
        std::cout<<"Failed to load spaceship!\n";
        return EXIT_FAILURE;
    }

    if( !loadBulletTexture(gameRenderer,bulletTexture)){
        std::cout<<"Failed to load bullet!\n";
        return EXIT_FAILURE;
    }

    std::vector<Bullet> bulletsOnScreen;

    bool quit = false;
    SDL_Event e;

    while(!quit){
    // Handle events (quitting, one-time actions like shooting)
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
        }
        if (e.type == SDL_KEYDOWN && e.key.repeat == 0) { 
            if (e.key.keysym.scancode == SDL_SCANCODE_SPACE) {
                ship.fireBullet(bulletsOnScreen); // Only fires once per key press
            }
        }
    }

    // Continuous movement logic (runs every frame)
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    if (currentKeyStates[SDL_SCANCODE_UP]) 
        ship.moveForward();
    if (currentKeyStates[SDL_SCANCODE_DOWN]) 
        ship.moveBackward();
    if (currentKeyStates[SDL_SCANCODE_LEFT]) 
        ship.rotateCounterClockwise();
    if (currentKeyStates[SDL_SCANCODE_RIGHT]) 
        ship.rotateClockwise();

    // Update screen
        SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 0xFF);
        SDL_RenderClear(gameRenderer);

        spaceshipTexture.render(gameRenderer,ship.getXpos(),ship.getYpos(),ship.getAngle());
        
        for(auto& bul : bulletsOnScreen){
            SDL_Point cen = {bul.getCenterX(),bul.getCenterY()};
            bulletTexture.render(gameRenderer,bul.getXpos(),bul.getYpos(),bul.getAngle(),&cen);
            bul.move(1);
        }
        SDL_RenderPresent(gameRenderer);
    }

    spaceshipTexture.free();
    bulletTexture.free();
    SDL_DestroyRenderer(gameRenderer);
    SDL_DestroyWindow(gameWindow);

    gameRenderer = NULL;
    gameWindow = NULL;
    SDL_Quit();
    IMG_Quit();
    return EXIT_SUCCESS;
}