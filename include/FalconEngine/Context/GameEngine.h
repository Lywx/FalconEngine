#pragma once

#include "Game.h"
#include "GameCounter.h"
#include "GameDebug.h"

namespace FalconEngine {

class GameEngine
{
public:
    // Runtime Constants
    double MillisecondPerUpdateMax = 16.66666666666;
    double MillisecondPerRender    = 16.66666666666;

    // Runtime Members
    Game *m_game;
    GameCounter Counter;

    explicit GameEngine(Game *game);

    // Copy Operations
    GameEngine(const GameEngine& rhs);
    GameEngine& operator=(const GameEngine& rhs);

    // Move Operations
    GameEngine(GameEngine&& rhs) noexcept;
    GameEngine& operator=(GameEngine&& rhs) noexcept;

    virtual ~GameEngine();

    virtual void Run();
    virtual void Shutdown();

protected:
    virtual void Initialize();

    // @Summary: Main loop
    // @Remark: The main goal of this algorithm is to ensure the render rate is
    // constant and update rate is flexible.
    virtual void Loop();

    virtual void Exit();

private:
    bool m_initialized = false;
    bool m_paused      = false;
    bool m_running     = true;
};

}