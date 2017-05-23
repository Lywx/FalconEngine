#include <FalconEngine/Context/Game.h>
#include <FalconEngine/Context/GameEngineGraphics.h>
#include <FalconEngine/Context/GameEngineSettings.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Game::Game() :
    mGameEngine(nullptr)
{
}

Game::~Game()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
GameEngine *
Game::GetEngine() const
{
    return mGameEngine;
}

void
Game::SetEngine(GameEngine *gameEngine)
{
    FALCON_ENGINE_CHECK_NULLPTR(gameEngine);

    mGameEngine = gameEngine;
}

void
Game::Initialize()
{
}

void
Game::Destory()
{
}

void
Game::RenderBegin(GameEngineGraphics *graphics)
{
    graphics->RenderBegin();
}

void
Game::Render(GameEngineGraphics *graphics, double percent)
{
    graphics->Render(percent);
}

void
Game::RenderEnd(GameEngineGraphics *graphics)
{
    graphics->RenderEnd();
}

void
Game::Update(GameEngineInput * /* input */, double /* elapsed */)
{
}

}
