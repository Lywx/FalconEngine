#include <FalconEngine/Context/GameEngineInput.h>

#include <FalconEngine/Context/GameEngineSettings.h>
#include <FalconEngine/Input/MouseState.h>
#include <FalconEngine/Input/KeyboardState.h>

#if defined(FALCON_ENGINE_WINDOW_GLFW)
#include <FalconEngine/Context/Platform/GLFW/GLFWGameEngineData.h>
#endif

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
    InitializePlatform();
}

void
GameEngineInput::Update(double elapsed)
{
    // NOTE(Wuxiang): Have to poll events before updating based on events.
    PollEvent();

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
