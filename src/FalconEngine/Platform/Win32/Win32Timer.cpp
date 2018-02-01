#include <FalconEngine/Core/Timer.h>

#if defined(FALCON_ENGINE_OS_WINDOWS)
#include <stdexcept>
#include <string>

#include <FalconEngine/Platform/Win32/Win32Lib.h>

namespace FalconEngine
{

/************************************************************************/
/* Platform Dependent Implementation                                    */
/************************************************************************/
class FALCON_ENGINE_API TimerImp
{
private:
    TimerImp()
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
        static TimerImp sInstance;
        return sInstance.mCounterFrequency;
    }

private:
    using Seconds = std::chrono::seconds;
    using SecondsPeriod = Seconds::period;

    using Milliseconds = std::chrono::milliseconds;
    using MillisecondsPeriod = Milliseconds::period;

    LARGE_INTEGER mCounterFrequency;
};

double
Timer::GetMilliseconds()
{
    return TimerImp::GetMilliseconds();
}

double
Timer::GetSeconds()
{
    return TimerImp::GetSeconds();
}

}

#endif
