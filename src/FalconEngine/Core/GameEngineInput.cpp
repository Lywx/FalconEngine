#include <FalconEngine/Core/GameEngineInput.h>

#include <FalconEngine/Core/GameEngineSettings.h>
#include <FalconEngine/Input/MouseState.h>
#include <FalconEngine/Input/KeyboardState.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
GameEngineInput::GameEngineInput() :
    mKeyboardState(std::make_shared<KeyboardState>()),
    mMouseState(std::make_shared<MouseState>())
{
}

GameEngineInput::~GameEngineInput()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
GameEngineInput::Destroy()
{
}

KeyboardState *
GameEngineInput::GetKeyboardState() const
{
    return mKeyboardState.get();
}

MouseState *
GameEngineInput::GetMouseState() const
{
    return mMouseState.get();
}

void
GameEngineInput::Initialize()
{
}

void
GameEngineInput::UpdateFrame(double elapsed)
{
    // NOTE(Wuxiang): Have to poll events before updating based on events.
    PollEventPlatform();

    // NOTE(Wuxiang): Update based on events pulled.
    UpdateEvent(elapsed);
}

void
GameEngineInput::UpdateEvent(double elapsed)
{
    mKeyboardState->UpdateEvent(elapsed);
    mMouseState->UpdateEvent(elapsed);
}

}
