#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLShaderBuffer.h>

#include <cstring>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformShaderBuffer::PlatformShaderBuffer(const ShaderBuffer *storageBuffer) :
    mBufferPtr(storageBuffer)
{
    Create();
}

PlatformShaderBuffer::~PlatformShaderBuffer()
{
    glDeleteBuffers(1, &mBufferObj);
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformShaderBuffer::Enable(unsigned int bindingIndex, int64_t offset, int64_t size)
{
    glBindBufferRange(GL_SHADER_STORAGE_BUFFER, bindingIndex, mBufferObj, offset, size);
}

void
PlatformShaderBuffer::Disable()
{
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void *
PlatformShaderBuffer::Map(BufferAccessMode          access,
                          BufferFlushMode           flush,
                          BufferSynchronizationMode synchronization,
                          int64_t                   offset,
                          int64_t                   size)
{
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, mBufferObj);
    GLvoid *data = glMapBufferRange(GL_SHADER_STORAGE_BUFFER, offset, size,
                                    OpenGLBufferAccessModeMark[int(access)] |
                                    OpenGLBufferFlushModeMark[int(flush)] |
                                    OpenGLBufferSynchronizationModeMark[int(synchronization)]);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    return data;
}

void
PlatformShaderBuffer::Unmap()
{
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, mBufferObj);
    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
void
PlatformShaderBuffer::Create()
{
    // Generate buffer
    glGenBuffers(1, &mBufferObj);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, mBufferObj);

    // Allocate buffer storage
    glBufferData(GL_SHADER_STORAGE_BUFFER, mBufferPtr->GetCapacitySize(),
                 nullptr, OpenGLBufferUsage[int(mBufferPtr->GetUsage())]);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    if (mBufferPtr->GetStorageMode() == BufferStorageMode::Host)
    {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, mBufferObj);

        void *data = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_WRITE_ONLY);
        memcpy(data, mBufferPtr->GetData(), mBufferPtr->GetDataSize());
        glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    }
}

}
