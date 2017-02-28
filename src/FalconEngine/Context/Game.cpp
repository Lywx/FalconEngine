#include <FalconEngine/Context/Game.h>

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
        mGameEngineSettings->mGraphics->mWidth = 800;
        mGameEngineSettings->mGraphics->mHeight = 600;
    }

    return mGameEngineSettings;
}

void
Game::Initialize() {};

void
Game::Destory() {};

void
Game::RenderBegin() {}

void
Game::Render(const GameEngineGraphics *gra double percent) { }

void
Game::RenderEnd() {}

void
Game::Update(const GameEngineInput *input, double elapsed)
{
}

}
