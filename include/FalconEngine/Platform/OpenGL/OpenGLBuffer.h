#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Platform/OpenGL/OpenGLLib.h>
#include <FalconEngine/Platform/OpenGL/OpenGLMapping.h>

namespace FalconEngine
{

class Renderer;

FALCON_ENGINE_CLASS_BEGIN PlatformBuffer
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformBuffer(Renderer *, GLuint target, const Buffer * buffer);
    virtual ~PlatformBuffer();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    // @summary Map buffer data in the memory, so you could copy data into
    // the buffer by yourself.
    //
    // @return Buffer memory pointer
    void *
    Map(Renderer *,
        ResourceMapAccessMode access,
        ResourceMapFlushMode flush,
        ResourceMapSyncMode synchronization,
        int64_t offset,
        int64_t size);

    // @summary Unmap buffer.
    void
    Unmap(Renderer *);

    // @remark Offset is relative to the start of the currently mapped range of buffer.
    void
    Flush(Renderer *, int64_t offset, int64_t size);

protected:
    /************************************************************************/
    /* Protected Members                                                    */
    /************************************************************************/

    /************************************************************************/
    /* Utility Members                                                      */
    /************************************************************************/
    // @summary Check range is valid in the buffer.
    void
    CheckRange(int64_t offset, int64_t size);

    void
    PrintRange(const char *message, GLuint bufferTarget, int64_t offset, int64_t size);

private:
    /************************************************************************/
    /* Private Members                                                      */
    /************************************************************************/
    void
    CreateBuffer();

protected:
    GLuint        mBufferObj;
    const Buffer *mBufferPtr;
    GLuint        mBufferTarget;
};
FALCON_ENGINE_CLASS_END

}
#endif