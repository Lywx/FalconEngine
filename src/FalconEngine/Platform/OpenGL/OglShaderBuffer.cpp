#include <FalconEngine/Platform/OpenGL/OglShaderBuffer.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <cstring>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformShaderBuffer::PlatformShaderBuffer(const ShaderBuffer *storageBuffer) :
    PlatformBuffer(GL_SHADER_STORAGE_BUFFER, storageBuffer)
{
}

PlatformShaderBuffer::~PlatformShaderBuffer()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformShaderBuffer::Enable(unsigned int bindingIndex)
{
    glBindBuffer(mBufferTarget, mBufferObj);
    glBindBufferBase(mBufferTarget, bindingIndex, mBufferObj);
}

void
PlatformShaderBuffer::Disable()
{
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

}

#endif