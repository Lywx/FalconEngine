#pragma once

#include <FalconEngine/InputInclude.h>

#if FALCON_ENGINE_PLATFORM_GLFW
#include <FalconEngine/Context/Platform/GLFW/GLFWInclude.h>

namespace FalconEngine
{

class MouseControllerData
{
public:
    explicit MouseControllerData(GLFWwindow *window) :
        mWindow(window)
    {
    }

    ~MouseControllerData() = default;

public:
    GLFWwindow *mWindow = nullptr;
};

}

#endif