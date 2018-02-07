#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Graphics/Renderer/Resource/ShaderBuffer.h>
#include <FalconEngine/Platform/OpenGL/OpenGLLib.h>
#include <FalconEngine/Platform/OpenGL/OpenGLBuffer.h>

namespace FalconEngine
{

class Renderer;

class FALCON_ENGINE_API PlatformShaderBuffer : public PlatformBuffer
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformShaderBuffer(Renderer *renderer, const ShaderBuffer *storageBuffer);
    virtual ~PlatformShaderBuffer();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Enable(Renderer *, unsigned int bindingIndex);

    void
    Disable(Renderer *);
};

}

#endif