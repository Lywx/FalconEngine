#pragma once

#include <FalconEngine/Graphics/Renderers/RendererExtensions.h>
#include <FalconEngine/Graphics/Resources/VertexBuffer.h>

namespace FalconEngine {

class Renderer;

class FALCON_ENGINE_GRAPHICS_ITEM PlatformVertexBuffer
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    PlatformVertexBuffer(Renderer *renderer, const VertexBuffer *vbuffer);
    ~PlatformVertexBuffer();

    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/

    // NOTE(Wuxiang): The interface is designed this way because the DirectX
    // renderer probably need those parameters.

    // @Summar: Enable buffer in the renderer.
    void Enable(Renderer *, size_t vertexSize, size_t offset);

    // @Summar: Disable buffer in the renderer.
    void Disable(Renderer *);

    // @Summary: Access buffer data in the memory, so you could copy data into
    // the buffer by yourself.
    // @Return: buffer memory pointer
    void *AccessBuffer(BufferAccessMode mode);

    // @Summary: Close the buffer access pointer.
    void CloseBuffer();

private:
    GLuint m_buffer;
};

}
