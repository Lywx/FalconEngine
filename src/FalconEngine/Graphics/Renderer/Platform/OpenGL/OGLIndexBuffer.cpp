#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLIndexBuffer.h>

#include <cstring>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformIndexBuffer::PlatformIndexBuffer(const IndexBuffer *indexBuffer) :
    PlatformBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer)
{
}

PlatformIndexBuffer::~PlatformIndexBuffer()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformIndexBuffer::Enable()
{
    glBindBuffer(mBufferTarget, mBufferObj);
}

void
PlatformIndexBuffer::Disable()
{
    glBindBuffer(mBufferTarget, 0);
}

}
