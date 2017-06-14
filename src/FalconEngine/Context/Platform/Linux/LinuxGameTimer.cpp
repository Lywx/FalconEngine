#include <FalconEngine/Context/GameTimer.h>

#include <stdexcept>
#include <string>

#if defined(FALCON_ENGINE_OS_LINUX)
#include <math.h>
#include <time.h>

namespace FalconEngine
{

/************************************************************************/
/* Platform Dependent Implementation                                    */
/************************************************************************/
class FALCON_ENGINE_API GameTimerImp
{
public:
    static double
    GetMilliseconds()
    {
        timespec spec;
        clock_gettime(CLOCK_MONOTONIC_RAW, &spec);

        // Nanoseconds converts to milliseconds.
        double nsMilliseconds = spec.tv_nsec / 1.0e6;

        // Seconds converts to milliseconds.
        double sMilliseconds = spec.tv_sec * 1.0e3;
        return sMilliseconds + nsMilliseconds;
    }

    static double
    GetSeconds()
    {
        timespec spec;
        clock_gettime(CLOCK_MONOTONIC_RAW, &spec);

        // Nanoseconds converts to milliseconds.
        double nsSeconds = spec.tv_nsec / 1.0e9;

        // Seconds converts to milliseconds.
        double sSeconds = spec.tv_sec * 1.0e3;
        return sSeconds + nsSeconds;
    }
};

double
GameTimer::GetMilliseconds()
{
    return GameTimerImp::GetMilliseconds();
}

double
GameTimer::GetSeconds()
{
    return GameTimerImp::GetSeconds();
}

}

#endif
