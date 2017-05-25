#pragma once

#include <FalconEngine/Context/Header.h>

#include <chrono>
#include <memory>

namespace FalconEngine
{

// @summary Performance counter used for both the engine and the game.
class GameTimerImp;

#pragma warning(disable: 4251)
class FALCON_ENGINE_API GameTimer final
{
public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    static double
    GetMilliseconds();

private:
    static std::shared_ptr<GameTimerImp> sImplementation;
};
#pragma warning(default: 4251)

}