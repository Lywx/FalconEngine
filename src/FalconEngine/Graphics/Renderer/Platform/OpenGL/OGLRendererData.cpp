#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLRendererData.h>

namespace FalconEngine
{

PlatformRendererData::PlatformRendererData() :
    mState(new PlatformRendererState()),
    mWindow(nullptr)
{
}

PlatformRendererData::~PlatformRendererData()
{
    delete mState;
}

}
