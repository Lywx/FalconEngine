#pragma once

#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLMapping.h>
#include <FalconEngine/Graphics/Renderer/Resource/Sampler.h>

namespace FalconEngine
{

class FALCON_ENGINE_ITEM_GRAPHICS PlatformSampler
{
public:
    PlatformSampler(const Sampler *sampler);
    virtual ~PlatformSampler();

    void
    Enable(int textureUnit);

    void
    Disable(int textureUnit);

private:
    GLuint mSampler;
    GLuint mSamplerPrevious;
};

}
