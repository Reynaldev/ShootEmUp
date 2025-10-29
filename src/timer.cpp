#include "timer.h"

Timer::~Timer()
{
    this->startTicks = 0;
    this->pausedTicks = 0;
    this->paused = false;
    this->started = false;
}

void Timer::start()
{
    this->started = true;
    this->paused = false;

    // Get the current clock time 
    this->startTicks = SDL_GetTicks();
    this->pausedTicks = 0;
}

void Timer::stop()
{
    this->started = false;
    this->paused = false;

    // Clear tick variables
    this->startTicks = 0;
    this->pausedTicks = 0;
}

void Timer::pause()
{
    // If the timer is running and isn't already paused
    if (this->started && !this->paused)
    {
        // Pause
        this->paused = true;

        // Calculate the paused ticks
        this->pausedTicks = SDL_GetTicks() - this->startTicks;
        this->startTicks = 0;
    }
}

void Timer::resume()
{
    // If the timer is running and paused
    if (this->started && this->paused)
    {
        // Unpause
        this->paused = false;

        // Reset the starting and the paused ticks
        this->startTicks = SDL_GetTicks() - this->pausedTicks;
        this->pausedTicks = 0;
    }
}

Uint32 Timer::getTicks()
{
    // The actual timer time
    Uint32 time = 0;

    // If the timer is running
    if (this->started)
    {
        // If the timer is paused
        if (this->paused)
        {
            // Return the number of ticks when the timer was paused
            time = this->pausedTicks;
        }
        else
        {
            // Return the current time minus the start time
            time = SDL_GetTicks() - this->startTicks;
        }
    }

    return time;
}

bool Timer::isStarted()
{
    return this->started;
}

bool Timer::isPaused()
{
    return this->paused;
}