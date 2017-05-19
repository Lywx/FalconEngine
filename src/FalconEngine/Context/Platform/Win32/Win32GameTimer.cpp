#include <FalconEngine/Context/GameTimer.h>

#if defined(FALCON_ENGINE_OS_WINDOWS)

#include <stdexcept>
#include <string>

#include <windows.h>

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
        if (!sTimerInitialized)
        {
            QueryPerformanceFrequency(&sCounterFrequency);
            sTimerInitialized = true;
        }
    }

    double
    GetMilliseconds() const
    {
        LARGE_INTEGER counter;
        QueryPerformanceCounter(&counter);

        // Millisecond: 1000    * counter / frequency / 1
        // Microsecond: 1000000 * counter / frequency / 1
        return MillisecondsPeriod::den * double(counter.QuadPart) / double(sCounterFrequency.QuadPart) / MillisecondsPeriod::num;
    }

private:
    using Milliseconds = std::chrono::milliseconds;
    using MillisecondsPeriod = Milliseconds::period;

    static LARGE_INTEGER sCounterFrequency;
    static bool          sTimerInitialized;
};

bool          GameTimerImp::sTimerInitialized = false;
LARGE_INTEGER GameTimerImp::sCounterFrequency;

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
