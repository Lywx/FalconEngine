#pragma once

#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLInclude.h>
#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLRendererState.h>

namespace FalconEngine
{

class PlatformRendererData sealed
{
public:
    PlatformRendererData();
    ~PlatformRendererData();

public:
    PlatformRendererState *mState;
    GLFWwindow            *mWindow;
};
}
