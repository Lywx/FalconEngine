#pragma once

#include <FalconEngine/ContextInclude.h>

#include <string>

namespace FalconEngine
{
class GameEngineGraphics;
class GameEngineInput;
class GameEngine;
class GameEngineSettings;
using GameEngineSettingsSharedPtr = std::shared_ptr<GameEngineSettings>;

// @summary This is the context that runs the customized code. The GameEngine class
// would use this class's
class Game
{
public:

    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Game();
    virtual ~Game();

    Game(const Game& rhs) = delete;
    Game& operator=(const Game& rhs) = delete;

public:
    /************************************************************************/
    /* Engine Operation                                                     */
    /************************************************************************/
    GameEngine *
    GetEngine() const
    {
        return mGameEngine;
    }

    void
    SetEngine(GameEngine *gameEngine)
    {
        FALCON_ENGINE_CHECK_NULLPTR(gameEngine);

        mGameEngine = gameEngine;
    }

    virtual GameEngineSettingsSharedPtr
    GetEngineSettings();

    /************************************************************************/
    /* Game Operation                                                       */
    /************************************************************************/
    virtual void
    Initialize();

    virtual void
    Destory();

    /************************************************************************/
    /* Render Operation                                                     */
    /************************************************************************/
    virtual void
    RenderBegin(GameEngineGraphics *graphics);

    virtual void
    Render(GameEngineGraphics *graphics, double percent);

    virtual void
    RenderEnd(GameEngineGraphics *graphics);

    /************************************************************************/
    /* Update Operation                                                     */
    /************************************************************************/

    // @param elapsed -- Millisecond elapsed during last update / render cycle.
    virtual void
    Update(GameEngineInput *input, double elapsed);

protected:
    GameEngine                 *mGameEngine;
    GameEngineSettingsSharedPtr mGameEngineSettings;
};

}
