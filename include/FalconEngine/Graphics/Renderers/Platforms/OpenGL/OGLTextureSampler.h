#pragma once

#include <FalconEngine/Graphics/Renderers/Platforms/OpenGL/OGLInclude.h>
#include <FalconEngine/Graphics/Renderers/Resources/Sampler.h>

namespace FalconEngine
{

class PlatformSampler
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
