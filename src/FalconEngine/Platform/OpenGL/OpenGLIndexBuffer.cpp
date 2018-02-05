#include <FalconEngine/Platform/OpenGL/OpenGLIndexBuffer.h>
#if defined(FALCON_ENGINE_API_OPENGL)
#include <cstring>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformIndexBuffer::PlatformIndexBuffer(Renderer *renderer, const IndexBuffer *indexBuffer) :
    PlatformBuffer(renderer, GL_ELEMENT_ARRAY_BUFFER, indexBuffer)
{
}

PlatformIndexBuffer::~PlatformIndexBuffer()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformIndexBuffer::Enable(Renderer *)
{
    glBindBuffer(mBufferTarget, mBufferObj);
}

void
PlatformIndexBuffer::Disable(Renderer *)
{
    glBindBuffer(mBufferTarget, 0);
}

}
#endif