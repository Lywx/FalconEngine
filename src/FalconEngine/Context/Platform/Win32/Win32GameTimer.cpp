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
private:
    GameTimerImp()
    {
        QueryPerformanceFrequency(&mCounterFrequency);
    }

public:
    static double
    GetMilliseconds()
    {
        LARGE_INTEGER counter;
        QueryPerformanceCounter(&counter);

        // Millisecond: 1000    * counter / frequency / 1
        // Microsecond: 1000000 * counter / frequency / 1
        return MillisecondsPeriod::den * double(counter.QuadPart) / double(GetCounterFrequency().QuadPart) / MillisecondsPeriod::num;
    }

    // TODO(Wuxiang): Need testing.
    static double
    GetSeconds()
    {
        LARGE_INTEGER counter;
        QueryPerformanceCounter(&counter);

        // Millisecond: 1000    * counter / frequency / 1
        // Microsecond: 1000000 * counter / frequency / 1
        return SecondsPeriod::den * double(counter.QuadPart) / double(GetCounterFrequency().QuadPart) / SecondsPeriod::num;
    }

private:
    static LARGE_INTEGER GetCounterFrequency()
    {
        static GameTimerImp sInstance;
        return sInstance.mCounterFrequency;
    }

private:
    using Seconds = std::chrono::milliseconds;
    using SecondsPeriod = Seconds::period;

    using Milliseconds = std::chrono::milliseconds;
    using MillisecondsPeriod = Milliseconds::period;

    LARGE_INTEGER mCounterFrequency;
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
