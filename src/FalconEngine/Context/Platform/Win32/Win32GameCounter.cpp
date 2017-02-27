#include <FalconEngine/Context/GameCounter.h>
#include <FalconEngine/Context/ContextInclude.h>

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
        if (!CounterInitialized)
        {
            QueryPerformanceFrequency(&CounterFrequency);
            CounterInitialized = true;
        }
    }

    double GetMilliseconds() const
    {
        LARGE_INTEGER counter;
        QueryPerformanceCounter(&counter);

        // Millisecond: 1000    * counter / frequency / 1
        // Microsecond: 1000000 * counter / frequency / 1
        return MillisecondsPeriod::den * double(counter.QuadPart) / double(CounterFrequency.QuadPart) / MillisecondsPeriod::num;
    }

private:
    typedef std::chrono::milliseconds Milliseconds;
    typedef Milliseconds::period      MillisecondsPeriod;

    static bool CounterInitialized;
    static LARGE_INTEGER CounterFrequency;
};

bool          GameCounterImp::CounterInitialized = false;
LARGE_INTEGER GameCounterImp::CounterFrequency;

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
GameCounter::GameCounter()
    : mInitializationPoint(std::chrono::steady_clock::now())
    , mImplementation(std::make_shared<GameCounterImp>(GameCounterImp()))
{
}

GameCounter::GameCounter(const GameCounter& rhs)
    : mInitializationPoint(rhs.mInitializationPoint)
    , mImplementation(rhs.mImplementation)
{
}

GameCounter& GameCounter::operator=(const GameCounter& rhs)
{
    mImplementation = rhs.mImplementation;
    mInitializationPoint = rhs.mInitializationPoint;

    return *this;
}

GameCounter::GameCounter(GameCounter&& rhs) noexcept
    : mInitializationPoint(rhs.mInitializationPoint)
    , mImplementation(rhs.mImplementation)
{
    rhs.mImplementation = nullptr;
}

GameCounter& GameCounter::operator=(GameCounter&& rhs) noexcept
{
    if (this != &rhs)
    {
        mImplementation = rhs.mImplementation;
        mInitializationPoint = rhs.mInitializationPoint;

        rhs.mImplementation = nullptr;
    }

    return *this;
}

GameCounter::~GameCounter()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
double GameCounter::GetMilliseconds() const
{
    return mImplementation->GetMilliseconds();
}

}

#endif
