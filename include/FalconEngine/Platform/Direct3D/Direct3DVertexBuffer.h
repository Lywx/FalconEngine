#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/ShaderBuffer.h>
#include <FalconEngine/Platform/Direct3D/Direct3DBuffer.h>

namespace FalconEngine
{

class Renderer;

class FALCON_ENGINE_API PlatformVertexBuffer : public PlatformBuffer
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformVertexBuffer(Renderer *renderer, const VertexBuffer *vertexBuffer);
    virtual ~PlatformVertexBuffer();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    // @Summar: Enable buffer in the renderer.
    void
    Enable(Renderer *renderer, unsigned int bindingIndex, int64_t offset, int stride);

    // @Summar: Disable buffer in the renderer.
    void
    Disable(Renderer *renderer, unsigned int bindingIndex);
};

}

#endif