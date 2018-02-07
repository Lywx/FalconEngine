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
PlatformUniformBuffer::Enable(Renderer *, unsigned bindingIndex)
{
    //glUniformBlockBinding()
    FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
}


}

#endif