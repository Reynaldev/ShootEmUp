#pragma once

#include "main.h"

class Timer
{
private:
    Uint32 startTicks = 0;
    Uint32 pausedTicks = 0;
    bool paused = false;
    bool started = false;
public:
    ~Timer();

    void start();
    void stop();
    void pause();
    void resume();

    Uint32 getTicks();

    bool isStarted();
    bool isPaused();
};