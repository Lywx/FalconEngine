#pragma once

#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLVertexBuffer.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformVertexBuffer::PlatformVertexBuffer(const VertexBuffer *vertexBuffer)
{
    // Generate buffer
    glGenBuffers(1, &mBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mBuffer);

    // Allocate buffer storage
    glBufferData(GL_ARRAY_BUFFER, vertexBuffer->GetDataByteNum(),
                 nullptr, OpenGLBufferUsage[int(vertexBuffer->GetUsage())]);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Copy the platform independent buffer data to platform specific buffer
    void *data = Map(BufferAccessMode::Write);

    // TODO(Wuxiang): Feed data without copying
    memcpy(data, vertexBuffer->GetData(), vertexBuffer->GetDataByteNum());
    Unmap();
}

PlatformVertexBuffer::~PlatformVertexBuffer()
{
    glDeleteBuffers(1, &mBuffer);
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformVertexBuffer::Enable(int bindingIndex, int offset, int stride)
{
    glBindVertexBuffer(bindingIndex, mBuffer, offset, stride);
}

void
PlatformVertexBuffer::Disable(int bindingIndex)
{
    glBindVertexBuffer(bindingIndex, 0, 0, 0);
}

void *
PlatformVertexBuffer::Map(BufferAccessMode mode)
{
    glBindBuffer(GL_ARRAY_BUFFER, mBuffer);

    // TODO(Wuxiang): Implement this using glMapBufferRange
    GLvoid *data = glMapBuffer(GL_ARRAY_BUFFER, OpenGLBufferAccessMode[int(mode)]);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return data;
}

void
PlatformVertexBuffer::Unmap()
{
    glBindBuffer(GL_ARRAY_BUFFER, mBuffer);
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

}
