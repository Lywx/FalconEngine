#pragma once

#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLMapping.h>
#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLBuffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexBuffer.h>

namespace FalconEngine
{

class FALCON_ENGINE_API PlatformVertexBuffer : public PlatformBuffer
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformVertexBuffer(const VertexBuffer *vertexBuffer);
    ~PlatformVertexBuffer();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    // @Summar: Enable buffer in the renderer.
    void
    Enable(unsigned int bindingIndex, int64_t offset, int stride);

    // @Summar: Disable buffer in the renderer.
    void
    Disable(unsigned int bindingIndex);
};

}
