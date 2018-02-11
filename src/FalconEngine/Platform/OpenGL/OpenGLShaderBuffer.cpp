#include <FalconEngine/Platform/OpenGL/OpenGLShaderBuffer.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <cstring>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformShaderBuffer::PlatformShaderBuffer(Renderer *renderer, const ShaderBuffer *storageBuffer) :
    PlatformBuffer(renderer, GL_SHADER_STORAGE_BUFFER, storageBuffer)
{
}

PlatformShaderBuffer::~PlatformShaderBuffer()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformShaderBuffer::Enable(Renderer *, unsigned int bindingIndex)
{
    glBindBuffer(mBufferTarget, mBufferObj);
    glBindBufferBase(mBufferTarget, bindingIndex, mBufferObj);
}

void
PlatformShaderBuffer::Disable(Renderer *)
{
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

}

#endif