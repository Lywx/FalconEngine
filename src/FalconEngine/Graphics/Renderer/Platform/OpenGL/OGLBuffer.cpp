#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLBuffer.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformBuffer::PlatformBuffer(GLuint target, const Buffer *buffer) :
    mBufferObj(0),
    mBufferPtr(buffer),
    mBufferTarget(target)
{
    Create();
}

PlatformBuffer::~PlatformBuffer()
{
    glDeleteBuffers(1, &mBufferObj);
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void *
PlatformBuffer::Map(BufferAccessMode          access,
                    BufferFlushMode           flush,
                    BufferSynchronizationMode synchronization,
                    int64_t                   offset,
                    int64_t                   size)
{
    glBindBuffer(mBufferTarget, mBufferObj);
    void *data = glMapBufferRange(mBufferTarget, offset, size,
                                  OpenGLBufferAccessModeMark[int(access)] |
                                  OpenGLBufferFlushModeMark[int(flush)] |
                                  OpenGLBufferSynchronizationModeMark[int(synchronization)]);
    glBindBuffer(mBufferTarget, 0);

    return data;
}

void
PlatformBuffer::Unmap()
{
    glBindBuffer(mBufferTarget, mBufferObj);
    glUnmapBuffer(mBufferTarget);
    glBindBuffer(mBufferTarget, 0);
}

void
PlatformBuffer::Flush(int64_t offset, int64_t size)
{
    glFlushMappedBufferRange(mBufferTarget, offset, size);
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
void
PlatformBuffer::Create()
{
    // Generate buffer.
    glGenBuffers(1, &mBufferObj);
    glBindBuffer(mBufferTarget, mBufferObj);

    // Allocate buffer storage.
    glBufferData(mBufferTarget, mBufferPtr->GetCapacitySize(), nullptr,
                 OpenGLBufferUsage[int(mBufferPtr->GetUsage())]);
    glBindBuffer(mBufferTarget, 0);

    if (mBufferPtr->GetStorageMode() == BufferStorageMode::Host)
    {
        glBindBuffer(mBufferTarget, mBufferObj);

        void *data = glMapBuffer(mBufferTarget, GL_WRITE_ONLY);
        memcpy(data, mBufferPtr->GetData() + mBufferPtr->GetDataOffset(), mBufferPtr->GetDataSize());
        glUnmapBuffer(mBufferTarget);

        glBindBuffer(mBufferTarget, 0);
    }
}

}
