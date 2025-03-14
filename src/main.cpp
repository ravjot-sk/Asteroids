#include "initialising.hpp"
#include "timer.hpp"
#include "collision.hpp"
#include "custom_math.hpp"
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

    //imgTexture asteroidTexture;

    std::vector<imgTexture> asteroidTextureVector;

    if (!loadSpaceshipTexture(gameRenderer,spaceshipTexture)){
        std::cout<<"Failed to load spaceship!\n";
        return EXIT_FAILURE;
    }

    if( !loadBulletTexture(gameRenderer,bulletTexture)){
        std::cout<<"Failed to load bullet!\n";
        return EXIT_FAILURE;
    }

    //if( !loadAsteroidTexture(gameRenderer,asteroidTexture)){
    //    std::cout<<"Failed to load asteroid!\n";
    //    return EXIT_FAILURE;
    //}

    if(!loadAsteroidVectorTextures(gameRenderer,asteroidTextureVector)){
        std::cout<<"Failed to load vector of asteroid textures!\n";
        return EXIT_FAILURE;
    }

    TTF_Font* scoreFont = NULL;
    if( !loadTextFont(&scoreFont, 50)){
        std::cout<<"\nFailed to load font!\n";
        return EXIT_FAILURE;
    }

    int totalAsteroidTextures = asteroidTextureVector.size();
/*     std::cout<<totalAsteroidTextures<<std::endl;

    //testing the textures
    SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 0xFF);
    SDL_RenderClear(gameRenderer);

    asteroidTextureVector[0].render(gameRenderer,0,0);
    asteroidTextureVector[1].render(gameRenderer, 500,0);
    asteroidTextureVector[2].render(gameRenderer, 1000,0);

    SDL_RenderPresent(gameRenderer);

 */
    std::list<Bullet> bulletsOnScreen;
    std::list<Asteroid> asteroidsOnScreen;
    int hitCounter = 0;
    
    //Want to pair an asteroid with the texture to use for the rendering
    std::list<std::pair<Asteroid,int> > asteroidTexturePair;


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

        //Add Asteroids every 3 seconds
        if(gameTimer.getTicks()/3000 >0){
            gameTimer.stop();
            asteroidsOnScreen.emplace_back();
            gameTimer.start();

            //Add a new asteroid and choose a texture for it randomly from the available ones
            int num = CustomMath::getRandomInt(0,totalAsteroidTextures-1);
            
            int h = asteroidTextureVector[num].getHeight();
            int w = asteroidTextureVector[num].getWidth();
            asteroidTexturePair.emplace_back(Asteroid(h,w),num);
        }

        //Render asteroids on screen and move them
        // for(auto& ast : asteroidsOnScreen){
        //     asteroidTexture.render(gameRenderer,ast.getXpos(),ast.getYpos(),ast.getAngle());
        //     ast.move();
        //     ast.rotate();
        // }

        //Render asteroids on screen using the chosen texture and move them
        for(auto & [ast,num] : asteroidTexturePair){
            asteroidTextureVector[num].render(gameRenderer,ast.getXpos(),ast.getYpos(),ast.getAngle());
            ast.move();
            ast.rotate();
        }
        
        //Bullet and Asteroid collision detection
        // for(auto& ast : asteroidsOnScreen){
        //     for(auto& bul : bulletsOnScreen){
        //         SDL_Rect bulRect = {bul.getXpos(),bul.getYpos(),bul.getWidth(),bul.getHeight()};
        //         SDL_Rect astRect = {ast.getXpos(),ast.getYpos(),ast.getWidth(),ast.getHeight()};
        //         if(areRectanglesColliding(&bulRect,&astRect)){
        //             bul.hitsTarget();
        //             ast.gotHit();
        //             hitCounter++;
        //         }
        //     }
        // }
        
        //Bullet and Asteroid collision detection2
        for( auto& [ast,num] : asteroidTexturePair){
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
//         asteroidsOnScreen.remove_if([](Asteroid ast){ return ast.isOffScreen();}); 

        //remove off screen asteroids2
        asteroidTexturePair.remove_if([](std::pair<Asteroid,int> &elem){
            return elem.first.isOffScreen();
        });
        //Rendering score
        scoreText.str("");
        scoreText<<"Score: "<<hitCounter;

        if( !scoreTexture.loadTextTexture(scoreText.str().c_str(),gameRenderer,scoreColor,scoreFont)){
            std::cout<<"Unable to render text!\n";
            return EXIT_FAILURE;
        }

        scoreTexture.render(gameRenderer,SCREEN_WIDTH-scoreTexture.getWidth()-30, 5);

        bool gameOver = false;

        //check spaceship and asteroid collision
        // for(auto& ast : asteroidsOnScreen){
        //     SDL_Rect spaceshipRect = {ship.getXpos(),ship.getYpos(),ship.getWidth()-10,ship.getHeight()-10};
        //     SDL_Rect astRect = {ast.getXpos(),ast.getYpos(),ast.getWidth()-10,ast.getHeight()-10};

        //     //if collided then quit the main event loop
        //     if(areRectanglesColliding(&spaceshipRect,&astRect)){
        //         gameOver = true;
        //         break;
        //     }
        // }

        //check spaceship and asteroid collision2
        for(auto& [ast,num] : asteroidTexturePair){
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
    //asteroidTexture.free();

    for(auto& ast: asteroidTextureVector){
        ast.free();
    }

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