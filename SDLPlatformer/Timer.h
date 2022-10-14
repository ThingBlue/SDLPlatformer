#pragma once

#include "Header.h"

namespace Biff
{
    class Timer
    {
    public:
        Timer() :
            startTime(timer::now())
        {

        }

        // Management function
        void reset()
        {
            startTime = timer::now();
        }

        // Information function
        float elapsed() const
        {
            return std::chrono::duration_cast<second>
                (timer::now() - startTime).count();
        }

    private:
        // High resolution timer
        typedef std::chrono::high_resolution_clock timer;
        typedef std::chrono::duration<float, std::ratio<1>> second;
        std::chrono::time_point<timer> startTime;
    };
}

