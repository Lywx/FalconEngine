#include <FalconEngine/Context/GameCounter.h>
#include <FalconEngine/ContextInclude.h>

#include <stdexcept>
#include <string>

#if BOOST_OS_WINDOWS
#include <windows.h>

namespace FalconEngine
{

/************************************************************************/
/* Platform Dependent Implementation                                    */
/************************************************************************/
class GameCounterImp
{
public:
    GameCounterImp()
    {
        if (!sCounterInitialized)
        {
            QueryPerformanceFrequency(&sCounterFrequency);
            sCounterInitialized = true;
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
    typedef std::chrono::milliseconds Milliseconds;
    typedef Milliseconds::period      MillisecondsPeriod;

    static bool          sCounterInitialized;
    static LARGE_INTEGER sCounterFrequency;
};

bool          GameCounterImp::sCounterInitialized = false;
LARGE_INTEGER GameCounterImp::sCounterFrequency;

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