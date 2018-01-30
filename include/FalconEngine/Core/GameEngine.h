#pragma once

#include <FalconEngine/Core/Game.h>
#include <FalconEngine/Core/GameEngineDebugger.h>
#include <FalconEngine/Core/Timer.h>

namespace FalconEngine
{

class GameEngineData;
class GameEngineGraphics;
class GameEngineInput;
class GameEnginePlatform;
class GameEngineProfiler;

FALCON_ENGINE_CLASS_BEGIN GameEngine
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit GameEngine(Game * game);
    virtual ~GameEngine();
    GameEngine(const GameEngine & rhs) = delete;
    GameEngine& operator=(const GameEngine & rhs) = delete;

    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Run();

    void
    Exit();

private:
    /************************************************************************/
    /* Private Members                                                      */
    /************************************************************************/
    void
    Initialize();

    // @summary Main loop
    // @note The main goal of this algorithm is to ensure the render rate is
    // constant and update rate is flexible.
    void
    Loop();

    void
    Destory();

private:
    /************************************************************************/
    /* Context Components                                                   */
    /************************************************************************/
    GameEngineData     *mData;
    Game               *mGame;
    GameEngineGraphics *mGraphics;
    GameEngineInput    *mInput;
    GameEnginePlatform *mPlatform;
    GameEngineProfiler *mProfiler;
    GameEngineSettings *mSettings;

    /************************************************************************/
    /* Context States                                                       */
    /************************************************************************/
    bool mInitialized = false;
    bool mPaused      = false;
    bool mRunning     = true;

    /************************************************************************/
    /* Context Threading                                                    */
    /************************************************************************/
    std::mutex mMutex;
};
FALCON_ENGINE_CLASS_END

}