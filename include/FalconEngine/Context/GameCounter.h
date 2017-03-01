#pragma once

#include <chrono>
#include <memory>

namespace FalconEngine
{

class GameCounterImp;
class GameCounter sealed
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
