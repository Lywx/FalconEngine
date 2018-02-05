#include <FalconEngine/Platform/OpenGL/OpenGLVertexBuffer.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <cstring>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformVertexBuffer::PlatformVertexBuffer(Renderer *renderer, const VertexBuffer *vertexBuffer) :
    PlatformBuffer(renderer, GL_ARRAY_BUFFER, vertexBuffer)
{
}

PlatformVertexBuffer::~PlatformVertexBuffer()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformVertexBuffer::Enable(Renderer *,
                             unsigned int bindingIndex,
                             int64_t offset,
                             int stride)
{
    glBindVertexBuffer(bindingIndex, mBufferObj, offset, stride);
}

void
PlatformVertexBuffer::Disable(Renderer *, unsigned int bindingIndex)
{
    glBindVertexBuffer(bindingIndex, 0, 0, 0);
}

}

#endif