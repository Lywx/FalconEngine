#pragma once

#include <chrono>
#include <memory>

namespace FalconEngine
{

// @summary Performance counter used for both the engine and the game.
class GameCounterImp;
class GameCounter final
{
public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    static double
    GetMilliseconds();

private:
    static std::shared_ptr<GameCounterImp> sImplementation;
};

}
