#include "initialising.hpp"
#include<string>

bool init(SDL_Window** gameWindow, SDL_Renderer** gameRenderer){
    bool success = true;
    
    //Initialise SDL
    if(SDL_Init(SDL_INIT_VIDEO)<0){
        std::cout<<"Failed to initialise SDL! SDL Error"<<SDL_GetError();
        success = false;
        return success;
    }
    
    //Set texture filtering to linear
    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ){
        std::cout<<"Warning: Linear texture filtering not enabled!";
    }
    
    //create Window
    *gameWindow = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(*gameWindow == NULL){
        std::cout<<"Failed to create window! SDL Error:"<<SDL_GetError();
        success = false;
        return success;
    }
    
    //creates a renderer that refreshes at the rate of the monitor vertical refresh rate
    *gameRenderer = SDL_CreateRenderer(*gameWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if( gameRenderer == NULL){
        std::cout<<"Failed to start renderer! SDL Error:"<<SDL_GetError();
        success = false;
        return success;
    }
    
    SDL_SetRenderDrawColor(*gameRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    
    //Initialise PNG Loading
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) ){
        std::cout<< "SDL_image could not initialize! SDL_image Error:"<< IMG_GetError()<<"\n";
        success = false;
        return success;
    }

    //Initialize SDL_ttf
    if( TTF_Init() == -1 ){
        std::cout<<"SDL_ttf could not initialize! SDL_ttf Error:"<< TTF_GetError()<<"\n";
        success = false;
    }

    return success;
}

bool loadSpaceshipTexture(SDL_Renderer* gameRenderer, imgTexture& spaceShipTexture){
    bool success = true;
    std::string assetsPath = ASSETS_PATH;

    if( !spaceShipTexture.loadImgTexture(assetsPath + "images/spaceship.png",gameRenderer) ){
        std::cout<<"Failed to load Spaceship texture!"<<std::endl;
        success = false;
    }
    return success;
}

bool loadBulletTexture(SDL_Renderer* gameRenderer, imgTexture& bulletTexture){
    bool success = true;
    std::string assetsPath = ASSETS_PATH;
    if ( !bulletTexture.loadImgTexture(assetsPath+"images/bullet.png",gameRenderer)){
        std::cout<<"Failed to load Bullet texture!"<<std::endl;
        success = false;
    }
    return success;
}

/*bool loadAsteroidTexture(SDL_Renderer* gameRenderer, imgTexture& asteroidTexture){
    bool success = true;
    std::string assetsPath = ASSETS_PATH;
    if( !asteroidTexture.loadImgTexture(assetsPath+"images/asteroid.png",gameRenderer)){
        std::cout<<"Failed to load Asteroid texture!"<<std::endl;
        success = false;
    }
    return success;
}*/

//loads all images to be used as asteroids as textures in the provided vector
bool loadAsteroidVectorTextures(SDL_Renderer* gameRenderer, std::vector<imgTexture>& asteroidTextureVector){
    bool success = true;
    std::string asteroidImgDirectoryPath = ASSETS_PATH;
    asteroidImgDirectoryPath = asteroidImgDirectoryPath + "images/asteroid_images";

    for(const auto & astImg : std::filesystem::directory_iterator(asteroidImgDirectoryPath)){
        if (astImg.path().extension() != ".png") {
            continue;  // Skip non-PNG files
        }
        std::cout<<astImg.path()<<std::endl;
        imgTexture temp;
        
        if(! temp.loadImgTexture(astImg.path(),gameRenderer)){
            std::cout<<"Failed to load Asteroid texture for image : "<<astImg.path()<<std::endl;
            success = false;
            break;
        }
        
        //move constructor used explicitly to prevent pointer issues with SDL_Texture* aTexture memeber of imgTexture class
        asteroidTextureVector.push_back(std::move(temp));
    }
    return success;
}

bool loadTextFont(TTF_Font** textFont, int fontSize){
    bool success = true;
    std::string assetsPath = ASSETS_PATH;
    std::string fontPath = assetsPath+"fonts/DotMatrixVar-ExpandedBold.ttf";
    *textFont = TTF_OpenFont(fontPath.c_str(),fontSize);
    if(textFont==NULL){
        std::cout<<"Failed to load font! SDL_TTF Error: "<<TTF_GetError()<<std::endl;
        success = false;
        return success;
    }
    return success;
}