#include <FalconEngine/Platform/OpenGL/OpenGLBuffer.h>
#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Core/Exception.h>
#include <FalconEngine/Core/GameEngineDebugger.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformBuffer::PlatformBuffer(Renderer *, GLuint target, const Buffer *buffer) :
    mBufferObj(0),
    mBufferPtr(buffer),
    mBufferTarget(target)
{
    CreateBuffer();
}

PlatformBuffer::~PlatformBuffer()
{
    glDeleteBuffers(1, &mBufferObj);
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void *
PlatformBuffer::Map(Renderer *,
                    ResourceMapAccessMode access,
                    ResourceMapFlushMode flush,
                    ResourceMapSyncMode synchronization,
                    int64_t offset,
                    int64_t size)
{
    glBindBuffer(mBufferTarget, mBufferObj);

    void *data = glMapBufferRange(mBufferTarget, offset, size,
                                  OpenGLBufferAccessModeBit[int(access)] |
                                  OpenGLBufferFlushModeBit[int(flush)] |
                                  OpenGLBufferSynchronizationModeBit[int(synchronization)]);
    glBindBuffer(mBufferTarget, 0);

    return data;
}

void
PlatformBuffer::Unmap(Renderer *)
{
    glBindBuffer(mBufferTarget, mBufferObj);
    glUnmapBuffer(mBufferTarget);
    glBindBuffer(mBufferTarget, 0);
}

void
PlatformBuffer::Flush(Renderer *, int64_t offset, int64_t size)
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
PlatformBuffer::CreateBuffer()
{
    // Generate buffer.
    glGenBuffers(1, &mBufferObj);
    glBindBuffer(mBufferTarget, mBufferObj);

    // Allocate buffer storage.
    glBufferData(mBufferTarget, mBufferPtr->GetCapacitySize(), nullptr,
                 OpenGLBufferUsage(mBufferPtr->GetAccessMode(), mBufferPtr->GetAccessUsage()));
    glBindBuffer(mBufferTarget, 0);

    auto storageMode = mBufferPtr->GetStorageMode();
    if (storageMode == ResourceStorageMode::Device)
    {
        // Do nothing.
    }
    else if (storageMode == ResourceStorageMode::Host)
    {
        glBindBuffer(mBufferTarget, mBufferObj);

        void *data = glMapBuffer(mBufferTarget, GL_WRITE_ONLY);
        memcpy(data, mBufferPtr->GetData() + mBufferPtr->GetDataOffset(), mBufferPtr->GetDataSize());
        glUnmapBuffer(mBufferTarget);

        glBindBuffer(mBufferTarget, 0);
    }
    else
    {
        FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
    }
}

}
#endif