# Custom Asteroid Game Generator

This program creates a basic asteroids game based on the images provided. Using the images provided in this repository, the game created looks like this:
<img width="1312" alt="Screenshot 2025-03-26 at 21 14 04" src="https://github.com/user-attachments/assets/5dd87400-d7e7-4256-a946-c5bbb932b6ce" />

However, one can use custom images for the spaceship, bullet, and the asteroids appearing in the game. Below is an example where I have used the images of my friends:
<img width="1304" alt="Screenshot 2025-03-27 at 00 42 45" src="https://github.com/user-attachments/assets/cdbd92d9-a641-4f9f-b7b6-508ecbc1cf61" />

## Prerequisites

### 1. A C++ compiler
If you already have a C++ compiler on your system, then you can directly proceed to the next step. However, if you don't have one, then the easiest way is to install XCode which comes with Apple Clang compiler. You can install XCode from the Mac App Store. 

### 2. CMake
The easiest way to install CMake is via [Homebrew](https://brew.sh/). Follow the install instructions for homebrew or run the following command on the terminal 
```
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

```
If you encounter an error with the above command, try running this command first
```
xcode-select --install
```
Once Homebrew is installed, run the following commands
```
brew update
brew install cmake
```

### 3. SDL2 Libraries
If you already have SDL2, SDL2_image, and SDL2_ttf set up on your system, then you can skip this step and CMake should be able to find the libraries itself. If you however encounter problems, then set up SDL2 in this way:

1. Download SDL2 dmg from the [SDL Release List](https://github.com/libsdl-org/SDL/releases) (I used SDL2 v2.30.10).
2. Open the dmg and copy the SDL2.framework folder to ~/Library/Frameworks directory.
3. Repeat 1. and 2. for SDL2_image from [SDL_image Release List](https://github.com/libsdl-org/SDL_image/releases) (I used SDL2_image v2.8.4), and for SDL2_ttf from [SDL_ttf Release List](https://github.com/libsdl-org/SDL_ttf/releases) (I used SDL2_ttf v2.24.0).

Note that it may happen that when the program first tries to use the SDL Libraries, Mac issues a warning 
>“SDL2.framework” can’t be opened because Apple cannot check it for malicious software
Follow the instructions on [here](https://support.apple.com/en-us/102445#:%7E:text=If%20you%27re%20certain%20that,security%20settings%20to%20open%20it.&text=Go%20to%20Security%20%26%20Privacy.,open%20or%20install%20the%20app.) to fix the issue.

## Building the project
Either clone the github repository to your system or download the zip and extract to the directory of your choice. Navigate to the code directory in the terminal and do the following:
```
mkdir build
cd build
cmake ..
```
At this point, CMake generates a bunch of messages. In case CMake is able to find SDL2, SDL2_image, and SDL2_ttf Libraries, it displays the locations of the libraries. Otherwise it will throw and error and needs troubleshooting. If no error is thrown, then run the following command to build the project
```
cmake --build .
```
This should generate the build files and create a binary that can be run from the terminal by
```
./Asteroids
```

## Using Custom Images
Once the build process works without problems and you can run the binary and play the game, you can generate a custom version of the game using personal photos. For this, navigate to the assets/images directory within the project. You can add as many images as you want in the asteroid_images directory and the program picks them at random to display as asteroids in the game. The recommended width of the images in this directory is <200 pixels. Also the background of the images needs to either be white or transparent.

For the spaceship and the bullet, you need to replace the given files with custom images with the same name. The recommended height of the spaceship is 100 pixels and for the bullet is 50 pixels. Again, the background either needs to be white or transparent.
