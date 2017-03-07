#pragma once

#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLInclude.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexBuffer.h>

namespace FalconEngine
{

class PlatformVertexBuffer
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    PlatformVertexBuffer(const VertexBuffer *vertexBuffer);
    ~PlatformVertexBuffer();

    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/

    // @Summar: Enable buffer in the renderer.
    void
    Enable(int bindingIndex, int offset, int stride);

    // @Summar: Disable buffer in the renderer.
    void
    Disable(int bindingIndex);

    // @summary Map buffer data in the memory, so you could copy data into
    // the buffer by yourself.
    //
    // @Return: buffer memory pointer
    void *
    Map(BufferAccessMode mode);

    // @summary Unmap buffer.
    void
    Unmap();

private:
    GLuint mBuffer;
};

}
