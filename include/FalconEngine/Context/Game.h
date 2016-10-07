#pragma once

namespace FalconEngine {

class GameEngine;

// @Summary: This is the context that runs the customized code. The GameEngine class
// would use this class's
class Game
{
public:

    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Game();

    // Copy Operations
    Game(const Game& rhs);
    virtual Game& operator=(const Game& rhs);

    // Move Operations
    Game(Game&& rhs) noexcept;
    virtual Game& operator=(Game&& rhs) noexcept;

    virtual ~Game();

    /************************************************************************/
    // Game Operation
    virtual void Initialize();
    virtual void Exit();

    /************************************************************************/
    // Render Operation
    virtual void RenderBegin();
    virtual void Render(double percent);
    virtual void RenderEnd();

    /************************************************************************/
    // Update Operation
    virtual void Update(double elapsed);
    virtual void UpdateInput();

    /************************************************************************/
    // Member Access Operation
    GameEngine *GetEngine() const;
    void        SetEngine(GameEngine *gameEngine);

protected:
    GameEngine *m_gameEngine = nullptr;
};

#include "Game.inl"

}