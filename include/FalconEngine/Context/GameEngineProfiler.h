#pragma once

#include <FalconEngine/Context/Header.h>

#include <memory>
#include <vector>

namespace FalconEngine
{

class GameEngineSettings;
using GameEngineSettingsSharedPtr = std::shared_ptr<GameEngineSettings>;

class GameEngineData;
using GameEngineDataSharedPtr = std::shared_ptr<GameEngineData>;

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
    Initialize(GameEngineDataSharedPtr gameEngineData, GameEngineSettingsSharedPtr gameEngineSettings);

    double
    GetLastFrameElapsedMillisecond() const
    {
        return mLastFrameElapsedMillisecond;
    }

    double
    GetLastFrameFPS() const
    {
        return mLastFrameFPS;
    }

    double
    GetLastFrameUpdateTotalCount() const
    {
        return mLastFrameUpdateTotalCount;
    }

    double
    GetLastUpdateElapsedMillisecond() const
    {
        return mLastUpdateElapsedMillisecond;
    }

    double
    GetLastRenderElapsedMillisecond() const
    {
        return mLastRenderElapsedMillisecond;
    }

private:
    double mLastFrameElapsedMillisecond;
    double mLastFrameFPS;
    int    mLastFrameUpdateTotalCount;

    double mLastUpdateElapsedMillisecond;
    double mLastRenderElapsedMillisecond;
};

}