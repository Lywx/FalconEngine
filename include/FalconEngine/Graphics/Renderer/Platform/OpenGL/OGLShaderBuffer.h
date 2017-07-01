#pragma once

#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLMapping.h>
#include <FalconEngine/Graphics/Renderer/Resource/ShaderBuffer.h>

namespace FalconEngine
{

class FALCON_ENGINE_API PlatformShaderBuffer
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformShaderBuffer(const ShaderBuffer *StorageBuffer);
    ~PlatformShaderBuffer();

    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    // @Summar: Enable buffer in the renderer.
    void
    Enable(unsigned int bindingIndex, int64_t offset, int64_t size);

    // @Summar: Disable buffer in the renderer.
    void
    Disable();

    // @summary Map buffer data in the memory, so you could copy data into
    // the buffer by yourself.
    //
    // @Return: buffer memory pointer
    void *
    Map(BufferAccessMode          access,
        BufferFlushMode           flush,
        BufferSynchronizationMode synchronization,
        int64_t                   offset,
        int64_t                   size);

    // @summary Unmap buffer.
    void
    Unmap();

private:
    /************************************************************************/
    /* Private Members                                                      */
    /************************************************************************/
    void
    Create();

private:
    GLuint              mBufferObj;
    const ShaderBuffer *mBufferPtr;
};

}
