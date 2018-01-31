#pragma once

#include <FalconEngine/Platform/OpenGL/OpenGLLib.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Graphics/Renderer/Resource/VertexBuffer.h>
#include <FalconEngine/Platform/OpenGL/OglBuffer.h>

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

#endif