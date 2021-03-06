#include <FalconEngine/Platform/OpenGL/OpenGLUniformBuffer.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Core/Exception.h>
#include <FalconEngine/Graphics/Renderer/Resource/UniformBuffer.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformUniformBuffer::PlatformUniformBuffer(Renderer *renderer, const UniformBuffer *uniformBuffer) :
    PlatformBuffer(renderer, GL_UNIFORM_BUFFER, uniformBuffer)
{
}

PlatformUniformBuffer::~PlatformUniformBuffer()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformUniformBuffer::Enable(Renderer *, unsigned int bindingIndex, unsigned int)
{
    glBindBufferBase(mBufferTarget, bindingIndex, mBufferObj);
}

void
PlatformUniformBuffer::Disable(Renderer *, unsigned int bindingIndex, unsigned int)
{
    glBindBufferBase(mBufferTarget, bindingIndex, 0);
}

void *
PlatformUniformBuffer::Map(Renderer *renderer)
{
    return PlatformBuffer::Map(renderer,
                               ResourceMapAccessMode::WriteBuffer,
                               ResourceMapFlushMode::Automatic,
                               ResourceMapSyncMode::Unsynchronized, 0,
                               mBufferPtr->GetCapacitySize());
}

}

#endif