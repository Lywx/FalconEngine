#include <FalconEngine/Context/Platform/GLFW/GLFWGameEngineInputDispatcher.h>
#include <FalconEngine/Context/GameTimer.h>

#if defined(FALCON_ENGINE_WINDOW_GLFW)

#include <FalconEngine/Context/GameEngineInput.h>
#include <FalconEngine/Context/Platform/GLFW/GLFWGameEngineData.h>

#include <FalconEngine/Input/MouseButton.h>
#include <FalconEngine/Input/MouseState.h>
#include <FalconEngine/Input/KeyboardState.h>
#include <FalconEngine/Input/KeyState.h>

namespace FalconEngine
{

void
KeyCallbackDispatch(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    auto dispatcher = reinterpret_cast<GameEngineInputDispatcher *>(glfwGetWindowUserPointer(window));
    if (dispatcher)
    {
        dispatcher->KeyCallback(window, key, scancode, action, mods);
    }
}

void
MouseButtonCallbackDispatch(GLFWwindow *window, int button, int action, int mods)
{
    auto dispatcher = reinterpret_cast<GameEngineInputDispatcher *>(glfwGetWindowUserPointer(window));
    if (dispatcher)
    {
        dispatcher->MouseButtonCallback(window, button, action, mods);
    }
}

void
ScrollCallbackDispatch(GLFWwindow *window, double xoffset, double yoffset)
{
    auto dispatcher = reinterpret_cast<GameEngineInputDispatcher *>(glfwGetWindowUserPointer(window));
    if (dispatcher)
    {
        dispatcher->ScrollCallback(window, xoffset, yoffset);
    }
}

void
MousePositionCallbackDispatch(GLFWwindow *window, double x, double y)
{
    auto dispatcher = reinterpret_cast<GameEngineInputDispatcher *>(glfwGetWindowUserPointer(window));
    if (dispatcher)
    {
        dispatcher->MousePositionCallback(window, x, y);
    }
}


/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
GameEngineInputDispatcher::GameEngineInputDispatcher(GameEngineInput *input) :
    mInput(input)
{
    auto window = GameEngineData::GetInstance()->mWindow;

    glfwSetKeyCallback(window, KeyCallbackDispatch);
    glfwSetMouseButtonCallback(window, MouseButtonCallbackDispatch);
    glfwSetCursorPosCallback(window, MousePositionCallbackDispatch);
    glfwSetScrollCallback(window, ScrollCallbackDispatch);

    glfwSetWindowUserPointer(window, this);

}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
void
GameEngineInputDispatcher::KeyCallback(GLFWwindow * /* window */, int key, int /* scancode */, int action, int /* mods */)
{
    auto keyPressed = action == GLFW_PRESS || action == GLFW_REPEAT;
    mInput->mKeyboardState->SetKeyInternal(Key(key), keyPressed, GameTimer::GetMilliseconds());
}

void
GameEngineInputDispatcher::MouseButtonCallback(GLFWwindow * /* window */, int button, int action, int /* mods */)
{
    mInput->mMouseState->SetButtonInternal(MouseButton(button), action == GLFW_PRESS, GameTimer::GetMilliseconds());
}

void
GameEngineInputDispatcher::ScrollCallback(GLFWwindow * /* window */, double /* xoffset */, double yoffset)
{
    mInput->mMouseState->SetWheelValueInternal(yoffset, GameTimer::GetMilliseconds());
}

void
GameEngineInputDispatcher::MousePositionCallback(GLFWwindow *window, double x, double y)
{
    static bool sScreenInitialized = false;;
    static int  sScreenHeight = 0;
    static int  sScreenWidth  = 0;

    // NOTE(Wuxiang): I invert the Y coordinate of screen space so that (0, 0)
    // as left lower corner to be consistent with the OpenGL NDC convention.
    if (!sScreenInitialized)
    {
        glfwGetWindowSize(window, &sScreenWidth, &sScreenHeight);
        sScreenInitialized = true;
    }

    mInput->mMouseState->SetPositionInternal(x, sScreenHeight - y, GameTimer::GetMilliseconds());
}

}

#endif
