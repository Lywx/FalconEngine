#include <FalconEngine/Core/GamePerformanceCounter.h>

#include <stdexcept>
#include <string>

#include <boost/predef.h>
#if BOOST_OS_WINDOWS
#include <windows.h>

namespace FalconEngine {
namespace Core {

/************************************************************************/
/* Platform Dependent Implementation                                    */
/************************************************************************/
class GamePerformanceCounterImp
{
public:
    GamePerformanceCounterImp()
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

bool          GamePerformanceCounterImp::CounterInitialized = false;
LARGE_INTEGER GamePerformanceCounterImp::CounterFrequency;

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
GamePerformanceCounter::GamePerformanceCounter()
    : m_initializationPoint(std::chrono::steady_clock::now())
    , m_implementation(std::make_shared<GamePerformanceCounterImp>(GamePerformanceCounterImp()))
{
}

GamePerformanceCounter::GamePerformanceCounter(const GamePerformanceCounter& rhs)
    : m_initializationPoint(rhs.m_initializationPoint)
    , m_implementation(rhs.m_implementation)
{
}

GamePerformanceCounter& GamePerformanceCounter::operator=(const GamePerformanceCounter& rhs)
{
    m_implementation = rhs.m_implementation;
    m_initializationPoint = rhs.m_initializationPoint;

    return *this;
}

GamePerformanceCounter::GamePerformanceCounter(GamePerformanceCounter&& rhs) noexcept
    : m_initializationPoint(rhs.m_initializationPoint)
    , m_implementation(rhs.m_implementation)
{
    rhs.m_implementation = nullptr;
}

GamePerformanceCounter& GamePerformanceCounter::operator=(GamePerformanceCounter&& rhs) noexcept
{
    if (this != &rhs)
    {
        m_implementation = rhs.m_implementation;
        m_initializationPoint = rhs.m_initializationPoint;

        rhs.m_implementation = nullptr;
    }

    return *this;
}

GamePerformanceCounter::~GamePerformanceCounter()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
double GamePerformanceCounter::GetMilliseconds() const
{
    return m_implementation->GetMilliseconds();
}

}
}

#endif
