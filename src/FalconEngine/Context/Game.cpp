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
Game::Render(double percent) { }

void
Game::RenderEnd() {}

void
Game::Update(double elapsed) { }

void
Game::UpdateInput() { }

}
