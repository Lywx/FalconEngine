#pragma once

#include <FalconEngine/Graphics/Renderers/OpenGL/PlatformVertexBuffer.h>
#include <FalconEngine/Graphics/Renderers/OpenGL/PlatformExtensions.h>

namespace FalconEngine {

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformVertexBuffer::PlatformVertexBuffer(Renderer *renderer, const VertexBuffer *vertexBuffer)
{
    // Generate new buffer
    glGenBuffers(1, &m_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
    glBufferData(GL_ARRAY_BUFFER,                                        // target
                 vertexBuffer->ByteNum(),                             // size
                 nullptr,                                                // data*
                 OpenGLBufferUsage[int(vertexBuffer->Usage())]);      // usage
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Copy the platform independent buffer data to platform specific buffer
    void *data = AccessBuffer(BufferAccessMode::WRITE);
    memcpy(data,                                                         // dest*
           vertexBuffer->Data(),                                      // src*
           vertexBuffer->ByteNum());                                  // count
    CloseBuffer();
}

PlatformVertexBuffer::~PlatformVertexBuffer()
{
    glDeleteBuffers(1, &m_buffer);
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void PlatformVertexBuffer::Enable(Renderer *, size_t, size_t)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
}

void PlatformVertexBuffer::Disable(Renderer *)
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void *PlatformVertexBuffer::AccessBuffer(BufferAccessMode mode)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
    GLvoid *data = glMapBuffer(GL_ARRAY_BUFFER, OpenGLBufferAccessMode[int(mode)]);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return data;
}

void PlatformVertexBuffer::CloseBuffer()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

}
