#include "timer.hpp"

GameTimer::GameTimer(){

    //Initialising variables
    startTicks = 0;
    pausedTicks = 0;

    paused = false;
    started = false;
}

void GameTimer::start(){
    //Start the timer
    started = true;

    //Unpause the timer
    paused = false;

    //Get current clock time
    startTicks = SDL_GetTicks();

    pausedTicks = 0;

}

void GameTimer::stop(){
    //Stop the timer
    started = false;

    paused = false;

    //Clear tick variables
    startTicks = 0;
    pausedTicks = 0;
}

void GameTimer::pause(){

    //Pause the timer only if it is started and not paused 
    if(started && !paused){
        paused = true;

        //Calculate the paused ticks
        pausedTicks = SDL_GetTicks() - startTicks;

        //Reset start ticks
        startTicks = 0;
    }
}

void GameTimer::unpause(){

    //Unpause the timer only if started and paused
    if(started && paused){
        paused = false;

        //Set the start ticks value
        startTicks = SDL_GetTicks() - pausedTicks;

        //Reset paused ticks
        pausedTicks = 0;
    }
}

Uint32 GameTimer::getTicks(){

    //Actual timer time
    Uint32 time =0;

    //If timer is running
    if(started){
        
        //If timer is paused
        if(paused){
            time = pausedTicks;
        }
        else{
            time = SDL_GetTicks() - startTicks;
        }
    }

    return time;
}

bool GameTimer::isStarted(){

    //return start state
    return started;
}

bool GameTimer::isPaused(){
    //return paused state
    return paused;
}