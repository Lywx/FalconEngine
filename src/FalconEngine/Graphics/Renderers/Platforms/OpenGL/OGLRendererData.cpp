#include <FalconEngine/Graphics/Renderers/Platforms/OpenGL/OGLRendererData.h>

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
