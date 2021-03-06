#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/ShaderBuffer.h>
#include <FalconEngine/Platform/Direct3D/Direct3DBuffer.h>

namespace FalconEngine
{

class Renderer;

class FALCON_ENGINE_API PlatformShaderBuffer : public PlatformBuffer
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformShaderBuffer(Renderer *renderer, const ShaderBuffer *shaderBuffer);
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