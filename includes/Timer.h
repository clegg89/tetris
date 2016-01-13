/**
 * @file Timer.h
 * 
 * @author C. Smith
 * @date Jan 7, 2016
 */

#ifndef _TIMER_H_
#define _TIMER_H_

#include <cstdint>

class TimerImpl;

class Timer
{
    protected:
        TimerImpl* pImpl;

    public:
        Timer();
        virtual ~Timer();

        uint32_t GetTicks();
};

#endif /* _TIMER_H_ */
