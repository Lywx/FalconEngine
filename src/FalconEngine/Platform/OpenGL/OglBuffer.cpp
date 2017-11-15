#include <FalconEngine/Platform/OpenGL/OglBuffer.h>

#include <FalconEngine/Core/GameEngineDebugger.h>

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
    glBindBuffer(mBufferTarget, mBufferObj);

    // NOTE(Wuxiang): Remember that the offset is related to mapped range.
    glFlushMappedBufferRange(mBufferTarget, offset, size);
    glBindBuffer(mBufferTarget, 0);
}

/************************************************************************/
/* Protected Members                                                    */
/************************************************************************/
void
PlatformBuffer::CheckRangeValid(int64_t offset, int64_t size)
{
#if defined(FALCON_ENGINE_DEBUG_GRAPHICS)
    glBindBuffer(mBufferTarget, mBufferObj);

    GLint bufferSize;
    glGetBufferParameteriv(mBufferTarget, GL_BUFFER_SIZE, &bufferSize);
    if (offset + size > bufferSize)
    {
        FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("Buffer is overflowed.");
    }

    glBindBuffer(mBufferTarget, 0);
#endif
}

void
PlatformBuffer::PrintRange(const char *message, GLuint bufferTarget, int64_t offset, int64_t size)
{
    GameEngineDebugger::OutputStringFormat("Buffer %s %s from %llu to %llu\n", std::to_string(bufferTarget).c_str(), message, offset, size);
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
