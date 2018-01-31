#pragma once

#include <FalconEngine/Core/Macro.h>

#include <chrono>
#include <memory>

namespace FalconEngine
{

// @summary Performance counter used for both the engine and the game.
class TimerImp;

#pragma warning(disable: 4251)
class FALCON_ENGINE_API Timer final
{
public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    static double
    GetMilliseconds();

    static double
    GetSeconds();
};
#pragma warning(default: 4251)

}
