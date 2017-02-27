#pragma once

#include <FalconEngine/Context/ContextInclude.h>

#include <string>

#include <FalconEngine/Context/GameEngineSettings.h>

namespace FalconEngine
{

class GameEngine;
class GameEngineSettings;

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
    RenderBegin();

    virtual void
    Render(double percent);

    virtual void
    RenderEnd();

    /************************************************************************/
    /* Update Operation                                                     */
    /************************************************************************/
    virtual void
    Update(double elapsed);

    virtual void
    UpdateInput();

protected:
    GameEngine                 *mGameEngine;
    GameEngineSettingsSharedPtr mGameEngineSettings;
};

}
