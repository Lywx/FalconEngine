#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLRendererData.h>

namespace FalconEngine
{

PlatformRendererData::PlatformRendererData(GLFWwindow *window) :
    mWindow(window)
{
    mState = std::make_unique<PlatformRendererState>();
}

PlatformRendererData::~PlatformRendererData()
{
}

}
