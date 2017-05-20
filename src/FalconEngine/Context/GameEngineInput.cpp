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
KeyboardStateSharedPtr
GameEngineInput::GetKeyboardState() const
{
    return mKeyboardState;
}

MouseStateSharedPtr
GameEngineInput::GetMouseState() const
{
    return mMouseState;
}

void
GameEngineInput::Initialize(GameEngineDataSharedPtr gameEngineData, GameEngineSettingsSharedPtr gameEngineSettings)
{
    mGameEngineData = gameEngineData;
    mGameEngineSettings = gameEngineSettings;

    InitializePlatform();
}

void
GameEngineInput::Update()
{
    // NOTE(Wuxiang): Have to poll events before updating based on events.
    PollEvent();

    // NOTE(Wuxiang): Update based on events pulled.
    UpdateEvent();
}

void
GameEngineInput::UpdateEvent()
{
    mMouseState->UpdateEvent();
}

}
