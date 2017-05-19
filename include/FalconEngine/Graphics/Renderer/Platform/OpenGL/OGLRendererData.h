#pragma once

#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLMapping.h>
#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLRendererState.h>

namespace FalconEngine
{

#pragma warning(disable: 4251)
class FALCON_ENGINE_API PlatformRendererData final
{
public:
    explicit PlatformRendererData(GLFWwindow *window);
    ~PlatformRendererData();

public:
    std::unique_ptr<PlatformRendererState> mState;
    GLFWwindow                            *mWindow;
};
#pragma warning(default: 4251)

}
