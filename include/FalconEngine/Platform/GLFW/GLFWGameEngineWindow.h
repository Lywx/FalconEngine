#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_WINDOW_GLFW)
#include <FalconEngine/Core/GameEngineSettings.h>
#include <FalconEngine/Platform/GLFW/GLFWLib.h>

namespace FalconEngine
{

class GameEngineData;
class GameEngineInput;

// @summary Game window represent the window system encapsulation. You would use
// same GameWindow class for different window system like, GLFW, Qt etc.
class FALCON_ENGINE_API PlatformGameEngineWindow
{
public:
    explicit PlatformGameEngineWindow(GLFWwindow *handle);
    ~PlatformGameEngineWindow();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Destroy();

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

    void
    WindowCloseCallback(GLFWwindow *window);

private:
    /************************************************************************/
    /* Private Members                                                      */
    /************************************************************************/
    void
    DestroyPlatform();

    void
    InitializeData();

    void
    InitializePlatform();

public:
    GLFWwindow *mHandle;

private:
    GameEngineData     *mData;
    GameEngineInput    *mInput;
    GameEngineSettings *mSettings;
};

}

#endif