#pragma once

#include <FalconEngine/Platform/OpenGL/OpenGLLib.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Graphics/Renderer/Resource/Sampler.h>

namespace FalconEngine
{

class FALCON_ENGINE_API PlatformSampler
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformSampler(const Sampler *sampler);
    virtual ~PlatformSampler();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Enable(int textureUnit);

    void
    Disable(int textureUnit);

private:
    GLuint mSampler;
    GLuint mSamplerPrevious;
};

}

#endif