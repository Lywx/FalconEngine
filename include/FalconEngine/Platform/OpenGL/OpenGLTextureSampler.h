#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Graphics/Renderer/Resource/Sampler.h>
#include <FalconEngine/Platform/OpenGL/OpenGLLib.h>

namespace FalconEngine
{

class Renderer;

class FALCON_ENGINE_API PlatformSampler final
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformSampler(Renderer *, const Sampler *sampler);
    ~PlatformSampler();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Enable(Renderer *, int textureUnit, unsigned int);

    void
    Disable(Renderer *, int textureUnit, unsigned int);

private:
    /************************************************************************/
    /* Private Members                                                      */
    /************************************************************************/
    void
    CreateSampler();

private:
    GLuint         mSamplerObj;
    GLuint         mSamplerObjPrevious;
    const Sampler *mSamplerPtr;
};

}

#endif