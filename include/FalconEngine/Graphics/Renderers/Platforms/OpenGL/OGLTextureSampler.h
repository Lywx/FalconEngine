#pragma once

#include <FalconEngine/Graphics/Renderers/Platforms/OpenGL/OGLInclude.h>
#include <FalconEngine/Graphics/Renderers/Resources/TextureSampler.h>

namespace FalconEngine
{

class PlatformTextureSampler
{
public:
    PlatformTextureSampler(const TextureSampler *sampler);
    virtual ~PlatformTextureSampler();

    void
    Enable(int textureUnit);

    void
    Disable(int textureUnit);

private:
    GLuint mSampler;
    GLuint mSamplerPrevious;
};

}
