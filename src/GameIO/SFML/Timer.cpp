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

        Int32 GetMilliSec();

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

Int32 TimerImpl::GetMilliSec()
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

uint32_t Timer::GetMilliSec()
{
    return this->pImpl->GetMilliSec();
}



