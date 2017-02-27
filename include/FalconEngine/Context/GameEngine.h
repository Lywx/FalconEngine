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
    void
    Run();

    void
    Exit();

private:
    void
    Initialize();

    // @summary Main loop
    // @note The main goal of this algorithm is to ensure the render rate is
    // constant and update rate is flexible.
    void
    Loop();

    void
    Destory();

public:
    double              mMillisecondPerUpdateMax = 16.66666666666;
    double              mMillisecondPerRender    = 16.66666666666;

private:
    GameCounter         mCounter;
    GameEngineData     *mData;
    Game               *mGame;
    GameEngineInput    *mInput;
    GameEnginePlatform *mPlatform;
    GameEngineGraphics *mGraphics;

    bool                mInitialized = false;
    bool                mPaused      = false;
    bool                mRunning     = true;
};

}