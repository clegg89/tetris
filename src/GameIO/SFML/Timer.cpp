/**
 * @file Timer.cpp
 * 
 * @author C. Smith
 * @date Jan 10, 2016
 */

#include <SFML/System.hpp>
#include <Timer.h>

using namespace sf;

class TimerImpl
{
    public:
        TimerImpl();
        virtual ~TimerImpl();

        Int32 GetTicks();

    private:
        Clock* pClock;
};

TimerImpl::TimerImpl()
{
    this->pClock = new Clock(); // Starts the clock;
}

TimerImpl::~TimerImpl()
{
    delete this->pClock;
}

Int32 TimerImpl::GetTicks()
{
    Time elapsed = this->pClock->getElapsedTime();

    return elapsed.asMilliseconds();
}

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



