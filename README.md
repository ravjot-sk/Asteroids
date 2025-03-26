# Custom Asteroid Game Generator
 
This program creates a basic asteroids game based on the images provided. One can use custom images for the spaceship, bullet, and multiple asteroids. 

## Building the project

I have tested the following build steps on macOS (Apple Silicon). Before following the steps, make sure that you have a C++ compiler on your system. The easiest way to do so is installing XCode on your system which comes with Apple Clang compiler. 

### 1.Setting up SDL2 Libraries
If you already have SDL2, SDL2_image, and SDL2_ttf set up on your system, then you can skip this step and CMake should be able to find the libraries itself. If you however encounter problems, then set up SDL2 in this way:

1. Download SDL2 dmg from the [SDL Release List](https://github.com/libsdl-org/SDL/releases). I used SDL2 v2.30.10. 
2. Open the dmg and copy the SDL2.framework folder to ~/Library/Frameworks directory.
3. Repeat this for SDL2_image from [SDL_image Release List](https://github.com/libsdl-org/SDL_image/releases) (I used SDL2_image v2.8.4), and for SDL2_ttf from [SDL_ttf Release List](https://github.com/libsdl-org/SDL_ttf/releases) (I used SDL2_ttf v2.24.0).

### 2. Clone the repository or download the code

