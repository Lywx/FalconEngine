#include <FalconEngine/Context/GameCounter.h>

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
class FALCON_ENGINE_API GameCounterImp
{
public:
    GameCounterImp()
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
GameCounter::GetMilliseconds()
{
    if (sImplementation == nullptr)
    {
        sImplementation = std::make_shared<GameCounterImp>();
    }

    return sImplementation->GetMilliseconds();
}

std::shared_ptr<GameCounterImp> GameCounter::sImplementation;

}

#endif