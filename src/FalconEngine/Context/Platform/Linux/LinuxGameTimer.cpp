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
    GameTimerImp()
    {
    }

    double
    GetMilliseconds() const
    {
        timespec spec;
        clock_gettime(CLOCK_MONOTONIC_RAW, &spec);

        // Nanoseconds converts to milliseconds.
        double nsMilliseconds = spec.tv_nsec / 1.0e6;

        // Seconds converts to milliseconds.
        double sMilliseconds = spec.tv_sec * 1.0e3;
        return sMilliseconds + nsMilliseconds;
    }
};

double
GameTimer::GetMilliseconds()
{
    if (sImplementation == nullptr)
    {
        sImplementation = std::make_shared<GameTimerImp>();
    }

    return sImplementation->GetMilliseconds();
}

std::shared_ptr<GameTimerImp> GameTimer::sImplementation;

}

#endif
