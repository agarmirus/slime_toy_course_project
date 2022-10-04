#ifndef TIMER_H
#define TIMER_H

#include <crono>
#include <thread>

class Timer
{
    public:
        virtual void tick(const size_t ms)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(ms));
        }
};

#endif TIMER_H
