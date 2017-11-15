#include <FalconEngine/Core/GameEngineWindow.h>
#include <FalconEngine/Core/Timer.h>

#if defined(FALCON_ENGINE_WINDOW_GLFW)
#include <FalconEngine/Core/GameEngineInput.h>
#include <FalconEngine/Input/MouseButton.h>
#include <FalconEngine/Input/MouseState.h>
#include <FalconEngine/Input/KeyboardState.h>
#include <FalconEngine/Input/KeyState.h>

namespace FalconEngine
{

class GameWindowDispatcher
{
public:
    static void
    KeyCallbackDispatch(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        auto w = reinterpret_cast<GameEngineWindow *>(glfwGetWindowUserPointer(window));
        if (w)
        {
            w->KeyCallback(window, key, scancode, action, mods);
        }
    }

    static void
    MouseButtonCallbackDispatch(GLFWwindow *window, int button, int action, int mods)
    {
        auto w = reinterpret_cast<GameEngineWindow *>(glfwGetWindowUserPointer(window));
        if (w)
        {
            w->MouseButtonCallback(window, button, action, mods);
        }
    }

    static void
    ScrollCallbackDispatch(GLFWwindow *window, double xoffset, double yoffset)
    {
        auto w = reinterpret_cast<GameEngineWindow *>(glfwGetWindowUserPointer(window));
        if (w)
        {
            w->ScrollCallback(window, xoffset, yoffset);
        }
    }

    static void
    MousePositionCallbackDispatch(GLFWwindow *window, double x, double y)
    {
        auto w = reinterpret_cast<GameEngineWindow *>(glfwGetWindowUserPointer(window));
        if (w)
        {
            w->MousePositionCallback(window, x, y);
        }
    }
};

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
GameEngineWindow::GameEngineWindow(GLFWwindow *handle) :
    mHandle(handle),
    mInput(nullptr),
    mSettings(nullptr)
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
GameEngineWindow::KeyCallback(GLFWwindow * /* window */, int key, int /* scancode */, int action, int /* mods */)
{
    auto keyPressed = action == GLFW_PRESS || action == GLFW_REPEAT;
    mInput->mKeyboardState->SetKeyInternal(Key(key), keyPressed, Timer::GetMilliseconds());
}

void
GameEngineWindow::MouseButtonCallback(GLFWwindow * /* window */, int button, int action, int /* mods */)
{
    mInput->mMouseState->SetButtonInternal(MouseButton(button), action == GLFW_PRESS, Timer::GetMilliseconds());
}

void
GameEngineWindow::MousePositionCallback(GLFWwindow *window, double x, double y)
{
    // NOTE(Wuxiang): I invert the Y coordinate of screen space so that (0, 0)
    // as left lower corner to be consistent with the OpenGL NDC convention.
    mInput->mMouseState->SetPositionInternal(x, mSettings->mWindowHeight - y, Timer::GetMilliseconds());
}

void
GameEngineWindow::ScrollCallback(GLFWwindow * /* window */, double /* xoffset */, double yoffset)
{
    mInput->mMouseState->SetWheelValueInternal(yoffset, Timer::GetMilliseconds());
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
void
GameEngineWindow::InitializeInputPlatform()
{
    glfwSetKeyCallback(mHandle, GameWindowDispatcher::KeyCallbackDispatch);
    glfwSetMouseButtonCallback(mHandle, GameWindowDispatcher::MouseButtonCallbackDispatch);
    glfwSetCursorPosCallback(mHandle, GameWindowDispatcher::MousePositionCallbackDispatch);
    glfwSetScrollCallback(mHandle, GameWindowDispatcher::ScrollCallbackDispatch);
    glfwSetWindowUserPointer(mHandle, this);
}

}

#endif