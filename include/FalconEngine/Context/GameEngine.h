#pragma once

#include <FalconEngine/Context/Game.h>
#include <FalconEngine/Context/GameTimer.h>
#include <FalconEngine/Context/GameDebug.h>

namespace FalconEngine
{

class GameEngineData;
using GameEngineDataSharedPtr = std::shared_ptr<GameEngineData>;
class GameEngineGraphics;
class GameEngineInput;
class GameEnginePlatform;
class GameEngineProfiler;

#pragma warning(disable: 4251)
class FALCON_ENGINE_API GameEngine
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
    /************************************************************************/
    /* Context Components                                                   */
    /************************************************************************/
    GameEngineDataSharedPtr     mData;
    Game                       *mGame;
    GameEngineGraphics         *mGraphics;
    GameEngineInput            *mInput;
    GameEnginePlatform         *mPlatform;
    GameEngineProfiler         *mProfiler;
    GameEngineSettingsSharedPtr mSettings;

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
#pragma warning(default: 4251)

}