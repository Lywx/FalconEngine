#pragma once

#include <FalconEngine/Input/Header.h>

#if FALCON_ENGINE_PLATFORM_GLFW
#include <FalconEngine/Context/Platform/GLFW/GLFWHeader.h>

namespace FalconEngine
{

class FALCON_ENGINE_ITEM_INPUT MouseControllerData
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