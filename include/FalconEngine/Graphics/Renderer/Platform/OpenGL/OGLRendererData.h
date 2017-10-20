#pragma once

#include <FalconEngine/Graphics/Common.h>

#include <FalconEngine/Core/Memory.h>
#include <FalconEngine/Context/GameEngineWindow.h>
#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/Common.h>
#if defined(FALCON_ENGINE_WINDOW_GLFW)
#include <FalconEngine/Graphics/Renderer/Platform/GLFW/GLFWWindowData.h>
#elif defined(FALCON_ENGINE_WINDOW_QT)
#include <FalconEngine/Graphics/Renderer/Platform/Qt/QtWindowData.h>
#endif

namespace FalconEngine
{

class PlatformWindowData;
FALCON_ENGINE_DELETER_DECLARE(PlatformWindowData, PlatformWindowDataDeleter);

#pragma warning(disable: 4251)
class FALCON_ENGINE_API PlatformRendererData final
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
#pragma warning(default: 4251)

}
#endif
