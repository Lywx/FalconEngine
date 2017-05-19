#pragma once

#include <FalconEngine/Context/Header.h>

#include <iostream>
#include <iomanip>

#include <FalconEngine/Context/GameTimer.h>

#define FALCON_ENGINE_DEBUG_TRACE_BLOCK() FalconEngine::GameTrace trace##__LINE__(__FUNCTION__)

namespace FalconEngine
{

// @summary Dignositic tracer used for both the engine and the game.
class FALCON_ENGINE_API GameTrace
{
public:
    explicit GameTrace(const char *functionName) :
        mFunctionName(functionName),
        mFunctionElapsedMillisecond(0)
    {
        mFunctionBeginMillisecond = GameTimer::GetMilliseconds();
    }


    ~GameTrace()
    {
        mFunctionElapsedMillisecond = GameTimer::GetMilliseconds() - mFunctionBeginMillisecond;
    }

private:
    const char *mFunctionName;
    double      mFunctionBeginMillisecond;
    double      mFunctionElapsedMillisecond;
};

}
