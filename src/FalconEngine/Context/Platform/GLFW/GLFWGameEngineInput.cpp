#include <FalconEngine/Context/GameEngineInput.h>

#include <FalconEngine/Input/MouseButton.h>
#include <FalconEngine/Input/MouseState.h>
#include <FalconEngine/Input/KeyboardState.h>
#include <FalconEngine/Input/KeyState.h>

#if defined(FALCON_ENGINE_WINDOW_GLFW)
#include <FalconEngine/Context/Platform/GLFW/GLFWGameEngineData.h>

namespace FalconEngine
{

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
void
GameEngineInput::DestroyPlatform()
{
}

void
GameEngineInput::InitializePlatform()
{
}

void
GameEngineInput::PollEvent()
{
    glfwPollEvents();
}

}

#endif
