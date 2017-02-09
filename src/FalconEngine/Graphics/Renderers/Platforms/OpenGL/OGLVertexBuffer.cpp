#pragma once

#include <FalconEngine/Graphics/Renderers/Platforms/OpenGL/OGLVertexBuffer.h>

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
    glBufferData(GL_ARRAY_BUFFER, vertexBuffer->mDataByteNum,
                 nullptr, OpenGLBufferUsage[int(vertexBuffer->mUsage)]);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Copy the platform independent buffer data to platform specific buffer
    void *data = Map(BufferAccessMode::Write);

    // TODO(Wuxiang): Feed data without copying
    memcpy(data, vertexBuffer->mData, vertexBuffer->mDataByteNum);
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
PlatformVertexBuffer::Enable()
{
    glBindBuffer(GL_ARRAY_BUFFER, mBuffer);
}

void
PlatformVertexBuffer::Disable()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
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
