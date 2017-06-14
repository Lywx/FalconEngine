#pragma once

#include <FalconEngine/Context/Header.h>

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

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    GameEngineProfiler() = default;
    ~GameEngineProfiler() = default;

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Initialize(GameEngineData *gameEngineData, GameEngineSettings *gameEngineSettings);

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
