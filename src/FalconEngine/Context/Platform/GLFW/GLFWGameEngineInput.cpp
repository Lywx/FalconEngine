#include <FalconEngine/Context/GameEngineInput.h>
#include <FalconEngine/Input/MouseButton.h>
#include <FalconEngine/Input/MouseController.h>
#include <FalconEngine/Input/MouseState.h>
#include <FalconEngine/Input/KeyboardState.h>
#include <FalconEngine/Input/KeyState.h>

#if FALCON_ENGINE_PLATFORM_GLFW
#include <FalconEngine/Context/Platform/GLFW/GLFWGameEngineData.h>
#include <FalconEngine/Input/Platform/GLFW/GLFWMouseControllerData.h>

namespace FalconEngine
{

class GameEngineInputDispatcher final
{
public:
    explicit GameEngineInputDispatcher(GameEngineInput *input);
    ~GameEngineInputDispatcher() = default;

    void
    KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

    void
    MouseButtonCallback(GLFWwindow *window, int button, int action, int mods);

    void
    ScrollCallback(GLFWwindow *window, double x, double y);

    void
    MousePositionCallback(GLFWwindow *window, double x, double y);

private:
    GameEngineInput *mInput;
};

GameEngineInputDispatcher::GameEngineInputDispatcher(GameEngineInput *input) :
    mInput(input)
{
}

void
GameEngineInputDispatcher::KeyCallback(GLFWwindow * /* window */, int key, int /* scancode */, int action, int /* mods */)
{
    auto keyPressed = action == GLFW_PRESS || action == GLFW_REPEAT;
    mInput->mKeyboardState->SetKeyInternal(Key(key), keyPressed, glfwGetTime());
}

void
GameEngineInputDispatcher::MouseButtonCallback(GLFWwindow * /* window */, int button, int action, int /* mods */)
{
    mInput->mMouseState->SetButtonInternal(MouseButton(button), action == GLFW_PRESS, glfwGetTime());
}

void
GameEngineInputDispatcher::ScrollCallback(GLFWwindow * /* window */, double /* xoffset */, double yoffset)
{
    mInput->mMouseState->SetWheelValueInternal(yoffset, glfwGetTime());
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

    mInput->mMouseState->SetPositionInternal(x, sScreenHeight - y, glfwGetTime());
}

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

void
GameEngineInput::InitializePlatform(const GameEngineData *data)
{
    mDispatcher = new GameEngineInputDispatcher(this);
    mMouseController->Initialize(std::make_shared<MouseControllerData>(data->mWindow));

    glfwSetKeyCallback(data->mWindow, KeyCallbackDispatch);
    glfwSetMouseButtonCallback(data->mWindow, MouseButtonCallbackDispatch);
    glfwSetCursorPosCallback(data->mWindow, MousePositionCallbackDispatch);
    glfwSetScrollCallback(data->mWindow, ScrollCallbackDispatch);

    glfwSetWindowUserPointer(data->mWindow, mDispatcher);
}

void
GameEngineInput::DestroyPlatform()
{
    delete mDispatcher;
}

void
GameEngineInput::PollEvent()
{
    glfwPollEvents();
}

}

#endif
