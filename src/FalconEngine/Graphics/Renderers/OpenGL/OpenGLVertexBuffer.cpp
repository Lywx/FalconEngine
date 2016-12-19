#pragma once

#include <FalconEngine/Graphics/Renderers/OpenGL/OpenGLVertexBuffer.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
OpenGLVertexBuffer::OpenGLVertexBuffer(const VertexBuffer *vertexBuffer)
{
    // Generate buffer
    glGenBuffers(1, &m_bufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferObject);

    // Allocate buffer storage
    glBufferData(GL_ARRAY_BUFFER, vertexBuffer->m_dataByteNum,
                 nullptr, OpenGLBufferUsage[int(vertexBuffer->m_usage)]);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Copy the platform independent buffer data to platform specific buffer
    void *data = Map(BufferAccessMode::Write);

    // TODO(Wuxiang): Feed data without copying
    memcpy(data, vertexBuffer->m_data, vertexBuffer->m_dataByteNum);
    Unmap();
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    glDeleteBuffers(1, &m_bufferObject);
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
OpenGLVertexBuffer::Enable()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferObject);
}

void
OpenGLVertexBuffer::Disable()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void *
OpenGLVertexBuffer::Map(BufferAccessMode mode)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferObject);

    glMapBufferRange
    GLvoid *data = glMapBuffer(GL_ARRAY_BUFFER, OpenGLBufferAccessMode[int(mode)]);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return data;
}

void
OpenGLVertexBuffer::Unmap()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferObject);
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

}
