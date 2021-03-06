#include <FalconEngine/Platform/GLFW/GLFWGameEngineWindow.h>

#if defined(FALCON_ENGINE_WINDOW_GLFW)
#include <FalconEngine/Core/GameEngineData.h>
#include <FalconEngine/Core/GameEngineInput.h>
#include <FalconEngine/Core/Timer.h>
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
        auto w = reinterpret_cast<PlatformGameEngineWindow *>(glfwGetWindowUserPointer(window));
        if (w)
        {
            w->KeyCallback(window, key, scancode, action, mods);
        }
    }

    static void
    MouseButtonCallbackDispatch(GLFWwindow *window, int button, int action, int mods)
    {
        auto w = reinterpret_cast<PlatformGameEngineWindow *>(glfwGetWindowUserPointer(window));
        if (w)
        {
            w->MouseButtonCallback(window, button, action, mods);
        }
    }

    static void
    ScrollCallbackDispatch(GLFWwindow *window, double xoffset, double yoffset)
    {
        auto w = reinterpret_cast<PlatformGameEngineWindow *>(glfwGetWindowUserPointer(window));
        if (w)
        {
            w->ScrollCallback(window, xoffset, yoffset);
        }
    }

    static void
    MousePositionCallbackDispatch(GLFWwindow *window, double x, double y)
    {
        auto w = reinterpret_cast<PlatformGameEngineWindow *>(glfwGetWindowUserPointer(window));
        if (w)
        {
            w->MousePositionCallback(window, x, y);
        }
    }

    static void
    WindowCloseCallbackDispatch(GLFWwindow *window)
    {

        auto w = reinterpret_cast<PlatformGameEngineWindow *>(glfwGetWindowUserPointer(window));
        if (w)
        {
            w->WindowCloseCallback(window);
        }
    }
};

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformGameEngineWindow::PlatformGameEngineWindow(GLFWwindow *handle) :
    mHandle(handle),
    mData(nullptr),
    mInput(nullptr),
    mSettings(nullptr)
{
}

PlatformGameEngineWindow::~PlatformGameEngineWindow()
{
    Destroy();
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformGameEngineWindow::Destroy()
{
    DestroyPlatform();
}

void
PlatformGameEngineWindow::Initialize()
{
    InitializeData();
    InitializePlatform();
}

void
PlatformGameEngineWindow::KeyCallback(GLFWwindow * /* window */, int key, int /* scancode */, int action, int /* mods */)
{
    auto keyPressed = action == GLFW_PRESS || action == GLFW_REPEAT;
    mInput->mKeyboardState->SetKeyInternal(Key(key), keyPressed, Timer::GetMilliseconds());
}

void
PlatformGameEngineWindow::MouseButtonCallback(GLFWwindow * /* window */, int button, int action, int /* mods */)
{
    mInput->mMouseState->SetButtonInternal(MouseButton(button), action == GLFW_PRESS, Timer::GetMilliseconds());
}

void
PlatformGameEngineWindow::MousePositionCallback(GLFWwindow *window, double x, double y)
{
    FALCON_ENGINE_UNUSE(window);

    // NOTE(Wuxiang): I invert the Y coordinate of screen space so that (0, 0)
    // as left lower corner to be consistent with the OpenGL NDC convention.
    mInput->mMouseState->SetPositionInternal(x, mSettings->mWindowHeight - y, Timer::GetMilliseconds());
}

void
PlatformGameEngineWindow::ScrollCallback(GLFWwindow * /* window */, double /* xoffset */, double yoffset)
{
    mInput->mMouseState->SetWheelValueInternal(yoffset, Timer::GetMilliseconds());
}

void
PlatformGameEngineWindow::WindowCloseCallback(GLFWwindow *window)
{
    FALCON_ENGINE_UNUSE(window);

    mData->mRunning = false;
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
void
PlatformGameEngineWindow::DestroyPlatform()
{
    glfwSetKeyCallback(mHandle, nullptr);
    glfwSetMouseButtonCallback(mHandle, nullptr);
    glfwSetCursorPosCallback(mHandle, nullptr);
    glfwSetScrollCallback(mHandle, nullptr);
    glfwSetWindowCloseCallback(mHandle, nullptr);
    glfwSetWindowUserPointer(mHandle, nullptr);
}

void
PlatformGameEngineWindow::InitializeData()
{
    mData = GameEngineData::GetInstance();
    mInput = GameEngineInput::GetInstance();
    mSettings = GameEngineSettings::GetInstance();
}

void
PlatformGameEngineWindow::InitializePlatform()
{
    glfwSetKeyCallback(mHandle, GameWindowDispatcher::KeyCallbackDispatch);
    glfwSetMouseButtonCallback(mHandle, GameWindowDispatcher::MouseButtonCallbackDispatch);
    glfwSetCursorPosCallback(mHandle, GameWindowDispatcher::MousePositionCallbackDispatch);
    glfwSetScrollCallback(mHandle, GameWindowDispatcher::ScrollCallbackDispatch);
    glfwSetWindowCloseCallback(mHandle, GameWindowDispatcher::WindowCloseCallbackDispatch);
    glfwSetWindowUserPointer(mHandle, this);
}

}

#endif