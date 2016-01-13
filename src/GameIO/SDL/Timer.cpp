/**
 * @file Timer.cpp
 * 
 * @author C. Smith
 * @date Jan 10, 2016
 */

#include <SDL.h>
#include <Timer.h>

class TimerImpl
{
    public:
        Uint32 GetTicks() { return SDL_GetTicks(); }
};

Timer::Timer()
{
    this->pImpl = new TimerImpl;
}

Timer::~Timer()
{
    delete this->pImpl;
}

uint32_t Timer::GetTicks()
{
    return this->pImpl->GetTicks();
}



