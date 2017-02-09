#include <FalconEngine/Context/Game.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Game::Game()
{

}

Game::Game(const Game& rhs)
{
}

Game& Game::operator=(const Game& rhs)
{
    return *this;
}

Game::Game(Game&& rhs) noexcept
{
}

Game& Game::operator=(Game&& rhs) noexcept
{
    return *this;
}

Game::~Game()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
Game::Initialize() {};

void
Game::Exit() {};

void
Game::RenderBegin() {}

void
Game::Render(double percent) { }

void
Game::RenderEnd() {}

void
Game::Update(double elapsed) { }

void
Game::UpdateInput() { }

void
Game::SetEngine(GameEngine *gameEngine)
{
    mGameEngine = gameEngine;
}

}
