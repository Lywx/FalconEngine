#pragma once

#include <FalconEngine/Core/Macro.h>

#include <iostream>
#include <iomanip>

#include <FalconEngine/Core/Timer.h>

#define FALCON_ENGINE_DEBUG_TRACE_BLOCK() FalconEngine::ProfileBlock pblock##__LINE__(__FUNCTION__)

namespace FalconEngine
{

// @summary Dignositic tracer used for both the engine and the game.
FALCON_ENGINE_CLASS_BEGIN ProfileBlock
{
public:
    explicit ProfileBlock(const char *functionName) :
        mFunctionName(functionName),
        mFunctionElapsedMillisecond(0)
    {
        mFunctionBeginMillisecond = Timer::GetMilliseconds();
    }


    ~ProfileBlock()
    {
        mFunctionElapsedMillisecond = Timer::GetMilliseconds() - mFunctionBeginMillisecond;
    }

private:
    const char *mFunctionName;
    double      mFunctionBeginMillisecond;
    double      mFunctionElapsedMillisecond;
};
FALCON_ENGINE_CLASS_END

}
