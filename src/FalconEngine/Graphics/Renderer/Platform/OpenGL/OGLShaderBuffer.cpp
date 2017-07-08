#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLShaderBuffer.h>

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
PlatformShaderBuffer::Enable()
{
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, mBufferObj);
}

void
PlatformShaderBuffer::Disable()
{
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

}
