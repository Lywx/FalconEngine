#pragma once

#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLMapping.h>
#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLRendererState.h>

namespace FalconEngine
{

class FALCON_ENGINE_ITEM_GRAPHICS PlatformRendererData final
{
public:
    PlatformRendererData();
    ~PlatformRendererData();

public:
    PlatformRendererState *mState;
    GLFWwindow            *mWindow;
};
}
