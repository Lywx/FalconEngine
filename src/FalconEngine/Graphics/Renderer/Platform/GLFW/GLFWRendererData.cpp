#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/GLFW/GLFWRendererData.h>

#if defined(FALCON_ENGINE_WINDOW_GLFW)

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

#endif