#pragma once

#include <FalconEngine/Context/Platform/GLFW/Common.h>

#if defined(FALCON_ENGINE_WINDOW_GLFW)

namespace FalconEngine
{

class GameEngineInput;

class FALCON_ENGINE_API GameEngineInputDispatcher final
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit GameEngineInputDispatcher(GameEngineInput *input);
    ~GameEngineInputDispatcher() = default;

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
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

}

#endif