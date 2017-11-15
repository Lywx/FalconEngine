#pragma once

#include <FalconEngine/Core/Common.h>

#include <memory>
#include <vector>

namespace FalconEngine
{

class GameEngineData;
class GameEngineSettings;

class FALCON_ENGINE_API GameEngineProfiler
{
    friend class GameEngine;

public:
    /************************************************************************/
    /* Static Members                                                       */
    /************************************************************************/
    static GameEngineProfiler *
    GetInstance()
    {
        static GameEngineProfiler sInstance;
        return &sInstance;
    }

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
