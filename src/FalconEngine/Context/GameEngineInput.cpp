#include <FalconEngine/Context/GameEngineInput.h>

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
