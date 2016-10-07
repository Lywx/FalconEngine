#include <FalconEngine/Context/GameCounter.h>
#include <FalconEngine/ContextInclude.h>

#include <stdexcept>
#include <string>

#if BOOST_OS_WINDOWS
#include <windows.h>

namespace FalconEngine {

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
    : m_initializationPoint(std::chrono::steady_clock::now())
    , m_implementation(std::make_shared<GameCounterImp>(GameCounterImp()))
{
}

GameCounter::GameCounter(const GameCounter& rhs)
    : m_initializationPoint(rhs.m_initializationPoint)
    , m_implementation(rhs.m_implementation)
{
}

GameCounter& GameCounter::operator=(const GameCounter& rhs)
{
    m_implementation = rhs.m_implementation;
    m_initializationPoint = rhs.m_initializationPoint;

    return *this;
}

GameCounter::GameCounter(GameCounter&& rhs) noexcept
    : m_initializationPoint(rhs.m_initializationPoint)
    , m_implementation(rhs.m_implementation)
{
    rhs.m_implementation = nullptr;
}

GameCounter& GameCounter::operator=(GameCounter&& rhs) noexcept
{
    if (this != &rhs)
    {
        m_implementation = rhs.m_implementation;
        m_initializationPoint = rhs.m_initializationPoint;

        rhs.m_implementation = nullptr;
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
    return m_implementation->GetMilliseconds();
}

}

#endif
