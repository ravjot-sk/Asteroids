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

bool init(SDL_Window** gameWindow, SDL_Renderer** gameRenderer);

bool loadSpaceshipTexture(SDL_Renderer* gameRenderer, gameTexture& spaceshipTexture );

bool loadBulletTexture(SDL_Renderer* gameRenderer, gameTexture& bulletTexture);

bool loadAsteroidTexture(SDL_Renderer* gameRenderer, gameTexture& asteroidTexture);

#endif