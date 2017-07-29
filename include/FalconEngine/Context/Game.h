#pragma once

#include <FalconEngine/Context/Common.h>

#include <mutex>
#include <string>

namespace FalconEngine
{
class GameEngineGraphics;
class GameEngineInput;
class GameEngine;
class GameEngineSettings;

// @summary This is the context that runs the customized code. The GameEngine class
// would use this class's
#pragma warning(disable: 4251)
class FALCON_ENGINE_API Game
{
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
public:
    Game();
    virtual ~Game();

    Game(const Game& rhs) = delete;
    Game& operator=(const Game& rhs) = delete;

public:
    /************************************************************************/
    /* Engine Operation                                                     */
    /************************************************************************/
    GameEngine *
    GetEngine() const;

    void
    SetEngine(GameEngine *gameEngine);

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
    // @remark This function is called at variable rate but at lease once per frame.
    // @param elapsed -- Millisecond elapsed during last update / render cycle.
    virtual void
    Update(GameEngineGraphics *graphics, GameEngineInput *input, double elapsed);

    // @remark This function is guaranteed to be called exactly once per frame.
    virtual void
    UpdateInput(GameEngineGraphics *graphics, GameEngineInput *input);

protected:
    GameEngine *mGameEngine;
};
#pragma warning(default: 4251)

}
