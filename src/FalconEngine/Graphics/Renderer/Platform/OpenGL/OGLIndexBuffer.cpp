#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLIndexBuffer.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformIndexBuffer::PlatformIndexBuffer(const IndexBuffer *indexBuffer)
{
    // Generate buffer
    glGenBuffers(1, &mBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffer);

    // Allocate buffer storage
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->GetCapacityByteNum(),
                 nullptr, OpenGLBufferUsage[int(indexBuffer->GetUsage())]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Copy the platform independent buffer data to platform specific buffer
    void *data = Map(BufferAccessMode::Write);

    // TODO(Wuxiang): Feed data without copying
    memcpy(data, indexBuffer->GetData(), indexBuffer->GetDataByteNum());
    Unmap();
}

PlatformIndexBuffer::~PlatformIndexBuffer()
{
    glDeleteBuffers(1, &mBuffer);
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformIndexBuffer::Enable()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffer);
}

void
PlatformIndexBuffer::Disable()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void *
PlatformIndexBuffer::Map(BufferAccessMode mode)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffer);

    // TODO(Wuxiang): Implement this using glMapBufferRange
    GLvoid *data = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, OpenGLBufferAccessMode[int(mode)]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    return data;
}

void
PlatformIndexBuffer::Unmap()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffer);
    glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

}
