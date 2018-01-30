#pragma once

#include <FalconEngine/Core/Common.h>

#if defined(FALCON_ENGINE_WINDOW_GLFW)
#include <FalconEngine/Core/GameEngineSettings.h>
#include <FalconEngine/Platform/GLFW/Common.h>

namespace FalconEngine
{

class GameEngineInput;

// @summary Game window represent the window system encapsulation. You would use
// same GameWindow class for different window system like, GLFW, Qt etc.
class FALCON_ENGINE_API GameEngineWindow
{
public:
    explicit GameEngineWindow(GLFWwindow *handle);
    ~GameEngineWindow() = default;

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Initialize();

    void
    KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

    void
    MouseButtonCallback(GLFWwindow *window, int button, int action, int mods);

    void
    MousePositionCallback(GLFWwindow *window, double x, double y);

    void
    ScrollCallback(GLFWwindow *window, double x, double y);

private:
    /************************************************************************/
    /* Private Members                                                      */
    /************************************************************************/
    void
    InitializeInputPlatform();

public:
    GLFWwindow         *mHandle;

private:
    GameEngineInput    *mInput;
    GameEngineSettings *mSettings;
};

}

#endif