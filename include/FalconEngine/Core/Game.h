#pragma once

#include "GameContext.h"
#include "GameCounter.h"
#include "GameDebug.h"

namespace FalconEngine {

class Game
{
public:
    // Runtime Constants
    double MillisecondPerUpdateMax = 16.66666666666;
    double MillisecondPerRender    = 16.66666666666;

    // Runtime Members
    GameContext *Context;
    GameCounter Counter;

    explicit Game(GameContext *context);

    // Copy Operations
    Game(const Game& rhs);
    Game& operator=(const Game& rhs);

    // Move Operations
    Game(Game&& rhs) noexcept;
    Game& operator=(Game&& rhs) noexcept;

    virtual ~Game();

    virtual void Run();
    virtual void Shutdown();

protected:
    virtual void Initialize();
    virtual void Loop();
    virtual void Exit();

private:
    bool m_initialized = false;
    bool m_paused      = false;
    bool m_running     = true;
};

}