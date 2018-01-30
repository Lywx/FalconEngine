#include <FalconEngine/Platform/OpenGL/OglVertexBuffer.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <cstring>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformVertexBuffer::PlatformVertexBuffer(const VertexBuffer *vertexBuffer) :
    PlatformBuffer(GL_ARRAY_BUFFER, vertexBuffer)
{
}

PlatformVertexBuffer::~PlatformVertexBuffer()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformVertexBuffer::Enable(unsigned int bindingIndex,
                             int64_t      offset,
                             int          stride)
{
    glBindVertexBuffer(bindingIndex, mBufferObj, offset, stride);
}

void
PlatformVertexBuffer::Disable(unsigned int bindingIndex)
{
    glBindVertexBuffer(bindingIndex, 0, 0, 0);
}

}

#endif