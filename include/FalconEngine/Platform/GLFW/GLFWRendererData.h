#pragma once

#include <FalconEngine/Core/Common.h>

#if defined(FALCON_ENGINE_WINDOW_GLFW)
#include <memory>

#include <FalconEngine/Core/GameEngineWindow.h>

namespace FalconEngine
{

FALCON_ENGINE_CLASS_BEGIN PlatformRendererData final
{
public:
    explicit PlatformRendererData();
    ~PlatformRendererData();

public:
    void
    Initialize(const std::shared_ptr<GameEngineWindow>& window);

public:
    GLFWwindow *mWindowHandle;
};
FALCON_ENGINE_CLASS_END

}
#endif
