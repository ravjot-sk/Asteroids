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

    if(!loadAsteroidVectorTextures(gameRenderer,asteroidTextureVector)){
        std::cout<<"Failed to load vector of asteroid textures!\n";
        return EXIT_FAILURE;
    }
    int totalAsteroidTextures = asteroidTextureVector.size();
    
    TTF_Font* scoreFont = NULL;
    if( !loadTextFont(&scoreFont, 50)){
        std::cout<<"\nFailed to load font!\n";
        return EXIT_FAILURE;
    }

    TTF_Font* titleFont = NULL;
    if(!loadTextFont(&titleFont, 80)){
        std::cout<<"\nFailed to load font for title!\n";
        return EXIT_FAILURE;
    }



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

    //Set up texture for title
    textTexture titleTexture;
    SDL_Color titleColor={0,255,0};
    if(!titleTexture.loadTextTexture("ASTEROIDS",gameRenderer,titleColor,titleFont)){
        std::cout<<"\nFailed to load title text texture!\n";
        return EXIT_FAILURE;
    }

    //Set up button to start the game

    TTF_Font* gameButtonFont =NULL;
    if(!loadTextFont(&gameButtonFont,30)){
        std::cout<<"\nFailed to load font for game buttons!\n";
        return EXIT_FAILURE;
    }

    textTexture startGameTexture;
    SDL_Color startGameColor = {255,255,255};
    if(!startGameTexture.loadTextTexture("Start Game",gameRenderer,startGameColor,gameButtonFont)){
        std::cout<<"Failed to load texture for \"Start Game\" button\n";
        return EXIT_FAILURE;
    }

    bool beginGame = false;
    bool quit = false;
    SDL_Event e;
    
    int titleXpos = (SCREEN_WIDTH - titleTexture.getWidth())/2;
    int titleYpos = 100;
    int startGameButtonXpos = (SCREEN_WIDTH - startGameTexture.getWidth())/2;
    int startGameButtonYpos = SCREEN_HEIGHT/2;
    SDL_Rect boundingStartButton = {startGameButtonXpos,startGameButtonYpos,startGameTexture.getWidth(),startGameTexture.getHeight()};
    
    //start screen
    while(!beginGame && !quit){
        bool highlightStartButton = false;
        while(SDL_PollEvent(&e)!=0){
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if(e.type == SDL_MOUSEBUTTONDOWN){
                int mouseX,mouseY;
                SDL_GetMouseState(&mouseX,&mouseY);
                if( mouseX > startGameButtonXpos && mouseX < startGameButtonXpos + startGameTexture.getWidth() && mouseY > startGameButtonYpos && mouseY <startGameButtonYpos + startGameTexture.getHeight())
                    beginGame = true;
            }
        }

        SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 0xFF);
        SDL_RenderClear(gameRenderer);

        titleTexture.render(gameRenderer,titleXpos, titleYpos);

        int mouseX,mouseY;
        SDL_GetMouseState(&mouseX,&mouseY);
        if( mouseX > startGameButtonXpos && mouseX < startGameButtonXpos + startGameTexture.getWidth() && mouseY > startGameButtonYpos && mouseY <startGameButtonYpos + startGameTexture.getHeight()){
            SDL_SetRenderDrawColor(gameRenderer,0,150,0,20);
            SDL_RenderFillRect(gameRenderer,&boundingStartButton);
        }

        startGameTexture.render(gameRenderer,startGameButtonXpos,startGameButtonYpos);

        SDL_RenderPresent(gameRenderer);
    }


    std::stringstream scoreText;


    GameTimer gameTimer;
    gameTimer.start();


    //main game starts
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

        //Render asteroids on screen using the chosen texture and move them
        for(auto & [ast,num] : asteroidTexturePair){
            asteroidTextureVector[num].render(gameRenderer,ast.getXpos(),ast.getYpos(),ast.getAngle());
            ast.move();
            ast.rotate();
        }
        
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

        //remove off screen asteroids2
        asteroidTexturePair.remove_if([](std::pair<Asteroid,int> &elem){
            return elem.first.isOffScreen();
        });

        //Check Asteroid Asteroid collision and bounce them off each other
        std::list<std::pair<Asteroid,int> >::iterator it1,it2;
        for(it1=asteroidTexturePair.begin(); it1!= asteroidTexturePair.end();it1++){
            for(it2 = std::next(it1); it2!= asteroidTexturePair.end();it2++){
                SDL_Rect astRect1 = {(it1->first).getXpos(),(it1->first).getYpos(), (it1->first).getWidth(),(it1->first).getHeight()};
                SDL_Rect astRect2 = {(it2->first).getXpos(),(it2->first).getYpos(), (it2->first).getWidth(),(it2->first).getHeight()};

                if(areRectanglesColliding(&astRect1,&astRect2)){
                    std::pair<int,int> center1 = {(astRect1.x + astRect1.w)/2, (astRect1.y + astRect1.h)/2};
                    std::pair<int,int> center2 = {(astRect2.x + astRect2.w)/2, (astRect2.y + astRect2.h)/2};
                    double newAngle1 = newAngleAfterCollision(center1,center2, (it1->first).getAngleMovement());
                    double newAngle2 = newAngleAfterCollision(center2, center1, (it2->first).getAngleMovement());
                    (it1->first).updateAngleMovement(newAngle1);
                    (it2->first).updateAngleMovement(newAngle2);
                }
            }
        }

        //Rendering score
        scoreText.str("");
        scoreText<<"Score: "<<hitCounter;

        if( !scoreTexture.loadTextTexture(scoreText.str().c_str(),gameRenderer,scoreColor,scoreFont)){
            std::cout<<"Unable to render text!\n";
            return EXIT_FAILURE;
        }

        scoreTexture.render(gameRenderer,SCREEN_WIDTH-scoreTexture.getWidth()-30, 5);

        bool gameOver = false;

        //check spaceship and asteroid collision2
        for(auto& [ast,num] : asteroidTexturePair){
            SDL_Rect spaceshipRect = {ship.getXpos(),ship.getYpos(),ship.getWidth()-10,ship.getHeight()-10};
            SDL_Rect astRect = {ast.getXpos(),ast.getYpos(),ast.getWidth()-10,ast.getHeight()-10};

            //if collided then quit the main event loop
            if(areRectanglesColliding(&spaceshipRect,&astRect)){
            //    gameOver = true;
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