#include <FalconEngine/Context/GameEngineInput.h>

#include <FalconEngine/Input/MouseButton.h>
#include <FalconEngine/Input/MouseState.h>
#include <FalconEngine/Input/KeyboardState.h>
#include <FalconEngine/Input/KeyState.h>

#if defined(FALCON_ENGINE_WINDOW_GLFW)
#include <FalconEngine/Context/Platform/GLFW/GLFWGameEngineData.h>
#include <FalconEngine/Context/Platform/GLFW/GLFWGameEngineInputDispatcher.h>

namespace FalconEngine
{

void
GameEngineInputDispatcherDeleter::operator()(GameEngineInputDispatcher *inputDispatcher)
{
    delete inputDispatcher;
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
void
GameEngineInput::InitializePlatform()
{
    mDispatcher = std::unique_ptr<GameEngineInputDispatcher, GameEngineInputDispatcherDeleter>(
                      new GameEngineInputDispatcher(this),
                      GameEngineInputDispatcherDeleter());
}

void
GameEngineInput::DestroyPlatform()
{
}

void
GameEngineInput::PollEvent()
{
    glfwPollEvents();
}

}

#endif
