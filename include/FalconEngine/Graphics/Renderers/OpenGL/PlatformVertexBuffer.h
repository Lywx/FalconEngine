#pragma once

#include <FalconEngine/Graphics/Renderers/RendererExtensions.h>
#include <FalconEngine/Graphics/Resources/VertexBuffer.h>

namespace FalconEngine {

class Renderer;

class PlatformVertexBuffer
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
    void Enable();
    void Disable();

    // @Summary: access buffer data in the memory
    // @Return: buffer memory pointer
    void *AccessBuffer(BufferAccessMode mode);

    // @Summary: close the buffer access pointer
    void CloseBuffer();

private:
    GLuint m_buffer;
};

}
