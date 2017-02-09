#pragma once

#include <chrono>
#include <memory>

namespace FalconEngine {

class GameCounterImp;
class GameCounter
{
public:
    GameCounter();

    // Copy Operation
    GameCounter(const GameCounter& rhs);
    GameCounter& operator=(const GameCounter& rhs);

    // Move Operation
    GameCounter(GameCounter&& rhs) noexcept;
    GameCounter& operator=(GameCounter&& rhs) noexcept;

    ~GameCounter();

    double GetMilliseconds() const;

private:
    std::chrono::time_point<std::chrono::steady_clock> mInitializationPoint;
    std::shared_ptr<GameCounterImp> mImplementation;
};

}
