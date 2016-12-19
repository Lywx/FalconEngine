#pragma once

#include <FalconEngine/GraphicsInclude.h>
#include <FalconEngine/Graphics/Renderers/VertexBuffer.h>
#include <FalconEngine/Graphics/Renderers/OpenGL/OpenGLInclude.h>

namespace FalconEngine
{

class Renderer;
class OpenGLVertexBuffer
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    OpenGLVertexBuffer(const VertexBuffer *vertexBuffer);
    ~OpenGLVertexBuffer();

    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/

    // @Summar: Enable buffer in the renderer.
    void
    Enable();

    // @Summar: Disable buffer in the renderer.
    void
    Disable();

    // @Summary: Map buffer data in the memory, so you could copy data into
    // the buffer by yourself.
    //
    // @Return: buffer memory pointer
    void *
    Map(BufferAccessMode mode);

    // @Summary: Unmap buffer.
    void Unmap();

private:
    GLuint m_bufferObject;
};

}
