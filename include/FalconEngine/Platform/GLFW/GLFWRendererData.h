#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_WINDOW_GLFW)
#include <memory>

#include <FalconEngine/Platform/GLFW//GLFWGameEngineWindow.h>

namespace FalconEngine
{

FALCON_ENGINE_CLASS_BEGIN PlatformRendererData final
{
public:
    explicit PlatformRendererData(GLFWwindow * windowHandle);
    ~PlatformRendererData();

public:
    GLFWwindow *mWindowHandle;
};
FALCON_ENGINE_CLASS_END

}
#endif
