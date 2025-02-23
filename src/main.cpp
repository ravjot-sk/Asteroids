#include "initialising.hpp"
#include "timer.hpp"
#include "collision.hpp"
#include <iostream>
#include <sstream>


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
    imgTexture spaceshipTexture;

    imgTexture bulletTexture;

    imgTexture asteroidTexture;

    if (!loadSpaceshipTexture(gameRenderer,spaceshipTexture)){
        std::cout<<"Failed to load spaceship!\n";
        return EXIT_FAILURE;
    }

    if( !loadBulletTexture(gameRenderer,bulletTexture)){
        std::cout<<"Failed to load bullet!\n";
        return EXIT_FAILURE;
    }

    if( !loadAsteroidTexture(gameRenderer,asteroidTexture)){
        std::cout<<"Failed to load asteroid!\n";
        return EXIT_FAILURE;
    }

    TTF_Font* scoreFont = NULL;
    if( !loadTextFont(&scoreFont, 50)){
        std::cout<<"\nFailed to load font!\n";
        return EXIT_FAILURE;
    }

    std::list<Bullet> bulletsOnScreen;
    std::list<Asteroid> asteroidsOnScreen;
    int hitCounter = 0;
    
    //Set up texture for score
    textTexture scoreTexture;
    //Transparency set at 190/255
    scoreTexture.setAlpha(190);
    //text color set at white
    SDL_Color scoreColor={255,255,255};
    std::stringstream scoreText;

    bool quit = false;
    SDL_Event e;

    GameTimer gameTimer;
    gameTimer.start();

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
        
        //Render each bullet and move it
        for(auto& bul : bulletsOnScreen){
            SDL_Point cen = {bul.getCenterX(),bul.getCenterY()};
            bulletTexture.render(gameRenderer,bul.getXpos(),bul.getYpos(),bul.getAngle(),&cen);
            bul.move();
        }

        //Add Asteroids every 5 seconds
        if(gameTimer.getTicks()/5000 >0){
            gameTimer.stop();
            asteroidsOnScreen.emplace_back();
            gameTimer.start();
        }

        //Render asteroids on screen and move them
        for(auto& ast : asteroidsOnScreen){
            asteroidTexture.render(gameRenderer,ast.getXpos(),ast.getYpos(),ast.getAngle());
            ast.move();
            ast.rotate();
        }
        
        for(auto& ast : asteroidsOnScreen){
            for(auto& bul : bulletsOnScreen){
                SDL_Rect bulRect = {bul.getXpos(),bul.getYpos(),bul.getWidth(),bul.getHeight()};
                SDL_Rect astRect = {ast.getXpos(),ast.getYpos(),ast.getWidth(),ast.getHeight()};
                if(areRectanglesColliding(&bulRect,&astRect)){
                    bul.hitsTarget();
                    ast.gotHit();
                    hitCounter++;
                }
            }
        }

        //remove off screen bullets
        bulletsOnScreen.remove_if([](Bullet bul){return bul.isOffScreen() ;});

        //remove off screen asteroids
        asteroidsOnScreen.remove_if([](Asteroid ast){ return ast.isOffScreen();});

        scoreText.str("");
        scoreText<<"Score: "<<hitCounter;

        if( !scoreTexture.loadTextTexture(scoreText.str().c_str(),gameRenderer,scoreColor,scoreFont)){
            std::cout<<"Unable to render text!\n";
            return EXIT_FAILURE;
        }

        scoreTexture.render(gameRenderer,SCREEN_WIDTH-scoreTexture.getWidth()-30, 5);

        bool gameOver = false;

        //check spaceship and asteroid collision
        for(auto& ast : asteroidsOnScreen){
            SDL_Rect spaceshipRect = {ship.getXpos(),ship.getYpos(),ship.getWidth()-10,ship.getHeight()-10};
            SDL_Rect astRect = {ast.getXpos(),ast.getYpos(),ast.getWidth()-10,ast.getHeight()-10};

            //if collided then quit the main event loop
            if(areRectanglesColliding(&spaceshipRect,&astRect)){
                gameOver = true;
                break;
            }
        }

        SDL_RenderPresent(gameRenderer);
        if(gameOver){
            break;
        }

    }

    //keep the screen until player closes the window
    while(!quit){
        while(SDL_PollEvent(&e)!=0){
            if(e.type== SDL_QUIT)
                quit = true;
        }
    }


    spaceshipTexture.free();
    bulletTexture.free();
    scoreTexture.free();

    SDL_DestroyRenderer(gameRenderer);
    SDL_DestroyWindow(gameWindow);
    TTF_CloseFont(scoreFont);

    gameRenderer = NULL;
    gameWindow = NULL;
    scoreFont = NULL;

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    return EXIT_SUCCESS;
}