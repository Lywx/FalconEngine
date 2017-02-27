#include <FalconEngine/Context/GameEngineInput.h>

#if FALCON_ENGINE_PLATFORM_GLFW
#include <FalconEngine/Context/Platform/GLFW/GLFWGameEngineData.h>

namespace FalconEngine
{

void
KeyCallbackDispatch(GLFWwindow *window, int key, int scancode, int action, int mods)
{

}

void
MouseButtonCallbackDispatch(GLFWwindow *window, int button, int action, int mods)
{
}

void
ScrollCallbackDispatch(GLFWwindow *window, double x, double y)
{
}

void
MousePositionCallbackDispatch(GLFWwindow *window, double x, double y)
{
}

void
GameEngineInput::InitializePlatform(const GameEngineData *data)
{
    glfwSetKeyCallback(data->mWindow, KeyCallbackDispatch);
    glfwSetMouseButtonCallback(data->mWindow, MouseButtonCallbackDispatch);
    glfwSetCursorPosCallback(data->mWindow, MousePositionCallbackDispatch);
    glfwSetScrollCallback(data->mWindow, ScrollCallbackDispatch);
}
}

#endif