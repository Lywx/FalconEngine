#include <FalconEngine/Context/GameEngineInput.h>
#include <FalconEngine/Context/GameEngineSettings.h>
#include <FalconEngine/Input/MouseController.h>
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
    mMouseController(std::make_shared<MouseController>()),
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

MouseControllerSharedPtr
GameEngineInput::GetMouseController() const
{
    return mMouseController;
}

MouseStateSharedPtr
GameEngineInput::GetMouseState() const
{
    return mMouseState;
}

void
GameEngineInput::Initialize(const GameEngineData *data, GameEngineSettingsSharedPtr settings)
{
    mSettings = settings->mInput;

    InitializePlatform(data);
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
