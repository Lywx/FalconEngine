#pragma once

#include <FalconEngine/Context/Game.h>
#include <FalconEngine/Context/GameCounter.h>
#include <FalconEngine/Context/GameDebug.h>

namespace FalconEngine
{

class GameEngineData;
class GameEngineGraphics;
class GameEngineInput;
class GameEnginePlatform;
class GameEngineProfiler;
class GameEngine
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit GameEngine(Game *game);
    virtual ~GameEngine();
    GameEngine(const GameEngine& rhs) = delete;
    GameEngine& operator=(const GameEngine& rhs) = delete;

    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    double
    GetMillisecondPerRender() const;

    void
    SetMillisecondPerRender(double millisecondPerRender);

    const GameEngineData *
    GetData() const;

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
    double mMillisecondPerRender = 16.66666666666;

    GameEngineData     *mData;
    Game               *mGame;
    GameEngineInput    *mInput;
    GameEnginePlatform *mPlatform;
    GameEngineProfiler *mProfiler;
    GameEngineGraphics *mGraphics;

    bool                mInitialized = false;
    bool                mPaused      = false;
    bool                mRunning     = true;
};

}