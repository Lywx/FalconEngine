#pragma once

#include <FalconEngine/Graphics/Renderers/Platforms/OpenGL/OGLInclude.h>
#include <FalconEngine/Graphics/Renderers/Platforms/OpenGL/OGLRendererState.h>

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
