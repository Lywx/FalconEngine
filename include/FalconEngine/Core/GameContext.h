#pragma once

namespace FalconEngine {
namespace Core {

class Game;
class GameContext
{
public:
    Game *Game = nullptr;

    GameContext();

    // Copy Operations
    GameContext(const GameContext& rhs);
    virtual GameContext& operator=(const GameContext& rhs);

    // Move Operations
    GameContext(GameContext&& rhs) noexcept;
    virtual GameContext& operator=(GameContext&& rhs) noexcept;

    virtual ~GameContext();

    virtual void Initialize();
    virtual void Exit();

    virtual void RenderBegin();
    virtual void Render(double percent);
    virtual void RenderEnd();

    virtual void Update(double elapsed);
    virtual void UpdateInput();
};

}
}