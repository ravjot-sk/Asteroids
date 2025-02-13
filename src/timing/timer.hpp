#ifndef TIMER_H
#define TIMER_H

#include "SDL2/SDL.h"

class GameTimer{
public:
    GameTimer();
    
    //Clock actions
    void start();
    void stop();
    void pause();
    void unpause();
    
    //Gets the timer's time
    Uint32 getTicks();
    
    //Check the status of the timer
    bool isStarted();
    bool isPaused();
    
private:
    //Clock time when the timer started
    Uint32 startTicks;
    
    //The Ticks stored when the timer was paused
    Uint32 pausedTicks;
    
    //The timer status
    bool paused;
    bool started;
};

#endif