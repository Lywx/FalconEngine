#include <FalconEngine/Context/Game.h>
#include <FalconEngine/Context/GameEngineGraphics.h>
#include <FalconEngine/Context/GameEngineGraphicsSettings.h>
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
GameEngineSettingsSharedPtr
Game::GetEngineSettings()
{
    if (!mGameEngineSettings)
    {
        mGameEngineSettings = std::make_shared<GameEngineSettings>();
        mGameEngineSettings->mGraphics->mWidth  = 800;
        mGameEngineSettings->mGraphics->mHeight = 600;
    }

    return mGameEngineSettings;
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
Game::Update(GameEngineInput *input, double elapsed)
{
}

}
