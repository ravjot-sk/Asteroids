#ifndef INITIALISED_H
#define INITIALISED_H

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "spaceship.hpp"
#include "bullet.hpp"
#include "texture.hpp"
#include "asteroid.hpp"
#include "game_constants.hpp"
#include <iostream>
#include <filesystem>

bool init(SDL_Window** gameWindow, SDL_Renderer** gameRenderer);

bool loadSpaceshipTexture(SDL_Renderer* gameRenderer, imgTexture& spaceshipTexture );

bool loadBulletTexture(SDL_Renderer* gameRenderer, imgTexture& bulletTexture);

//bool loadAsteroidTexture(SDL_Renderer* gameRenderer, imgTexture& asteroidTexture);

bool loadAsteroidVectorTextures(SDL_Renderer* gameRenderer, std::vector<imgTexture>& asteroidTextureVector);

bool loadTextFont(TTF_Font** textFont, int fontSize);
#endif