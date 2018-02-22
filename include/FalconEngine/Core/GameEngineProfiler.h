#pragma once

#include <FalconEngine/Core/Macro.h>

#include <memory>
#include <vector>

#include <FalconEngine/Core/Memory.h>

namespace FalconEngine
{

class GameEngineData;
class GameEngineSettings;

class FALCON_ENGINE_API GameEngineProfiler
{
    friend class GameEngine;

    FALCON_ENGINE_SINGLETON_SAFE_DECLARE(GameEngineProfiler);

    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
private:
    GameEngineProfiler() = default;

public:
    ~GameEngineProfiler() = default;

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Initialize();

    double
    GetLastFrameElapsedMillisecond() const;

    double
    GetLastFrameFps() const;

    double
    GetLastFrameUpdateTotalCount() const;

    double
    GetLastUpdateElapsedMillisecond() const;

    double
    GetLastRenderElapsedMillisecond() const;

private:
    double mLastFrameElapsedMillisecond;
    double mLastFrameFps;
    int    mLastFrameUpdateTotalCount;

    double mLastUpdateElapsedMillisecond;
    double mLastRenderElapsedMillisecond;
};

}
