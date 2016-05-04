#pragma once

#include <chrono>
#include <memory>

namespace FalconEngine {

class GamePerformanceCounterImp;
class GamePerformanceCounter
{
public:
    GamePerformanceCounter();

    // Copy Operation
    GamePerformanceCounter(const GamePerformanceCounter& rhs);
    GamePerformanceCounter& operator=(const GamePerformanceCounter& rhs);

    // Move Operation
    GamePerformanceCounter(GamePerformanceCounter&& rhs) noexcept;
    GamePerformanceCounter& operator=(GamePerformanceCounter&& rhs) noexcept;

    ~GamePerformanceCounter();

    double GetMilliseconds() const;

private:
    std::chrono::time_point<std::chrono::steady_clock> m_initializationPoint;
    std::shared_ptr<GamePerformanceCounterImp> m_implementation;
};

}
