#include <FalconEngine/Core/Game.h>
#include <FalconEngine/Core/GameEngineGraphics.h>
#include <FalconEngine/Core/GameEngineSettings.h>

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
Game::Update(GameEngineGraphics *graphics, GameEngineInput * /* input */, double elapsed)
{
    graphics->Update(elapsed);
}

void
Game::UpdateFrame(GameEngineGraphics *graphics, GameEngineInput * /* input */, double elapsed)
{
    graphics->UpdateFrame(elapsed);
}

}
