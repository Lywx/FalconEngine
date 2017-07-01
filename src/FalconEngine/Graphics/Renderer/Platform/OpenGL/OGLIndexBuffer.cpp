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
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBufferObj);
}

void
PlatformIndexBuffer::Disable()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

}
