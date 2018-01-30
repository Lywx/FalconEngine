#pragma once

#include <memory>

#include <FalconEngine/Core/Common.h>
#include <FalconEngine/Core/Memory.h>
#include <FalconEngine/Core/GameEngineWindow.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Platform/OpenGL/Common.h>
#if defined(FALCON_ENGINE_WINDOW_GLFW)
#include <FalconEngine/Platform/GLFW/GLFWWindowData.h>
#elif defined(FALCON_ENGINE_WINDOW_QT)
#include <FalconEngine/Platform/Qt/QtWindowData.h>
#endif

namespace FalconEngine
{

class PlatformWindowData;
FALCON_ENGINE_DELETER_DECLARE(PlatformWindowData, PlatformWindowDataDeleter);

FALCON_ENGINE_CLASS_BEGIN PlatformRendererData final
{
public:
    explicit PlatformRendererData();
    ~PlatformRendererData();

public:
    void
    Initialize(const std::shared_ptr<GameEngineWindow>& window);

public:
    std::unique_ptr<> mWindowData;
};
FALCON_ENGINE_CLASS_END

}
#endif
