#pragma once

#include <FalconEngine/Graphics/Renderers/Platforms/OpenGL/OGLInclude.h>
#include <FalconEngine/Graphics/Renderers/Platforms/OpenGL/OGLRenderState.h>

namespace FalconEngine
{

class RendererData
{
public:
    PlatformRenderState mState;
    GLFWwindow         *mWindow;
};

}
