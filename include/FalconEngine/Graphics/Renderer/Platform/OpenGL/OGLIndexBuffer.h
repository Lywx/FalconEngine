#pragma once

#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLMapping.h>
#include <FalconEngine/Graphics/Renderer/Resource/IndexBuffer.h>

namespace FalconEngine
{

class FALCON_ENGINE_API PlatformIndexBuffer
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    PlatformIndexBuffer(const IndexBuffer *indexBuffer);
    ~PlatformIndexBuffer();

    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Enable();

    void
    Disable();

    void *
    Map(BufferAccessMode mode);

    void
    Unmap();

private:
    GLuint mBuffer;
};

}