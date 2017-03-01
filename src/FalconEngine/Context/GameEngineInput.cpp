#include <FalconEngine/Context/GameEngineInput.h>
#include <FalconEngine/Context/GameEngineSettings.h>
#include <FalconEngine/Input/MouseState.h>
#include <FalconEngine/Input/KeyboardState.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
GameEngineInput::GameEngineInput() :
    mDispatcher(nullptr),
    mKeyboardState(std::make_shared<KeyboardState>()),
    mMouseState(std::make_shared<MouseState>())
{
}

GameEngineInput::~GameEngineInput()
{
    DestroyPlatform();
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
GameEngineInput::Initialize(const GameEngineData *data, GameEngineSettingsSharedPtr settings)
{
    mSettings = settings->mInput;

    InitializePlatform(data);
}

}
