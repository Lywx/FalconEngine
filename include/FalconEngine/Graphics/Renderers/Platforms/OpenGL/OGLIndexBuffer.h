#pragma once

#include <FalconEngine/Graphics/Renderers/Platforms/OpenGL/OGLInclude.h>
#include <FalconEngine/Graphics/Renderers/Resources/IndexBuffer.h>

namespace FalconEngine
{

class PlatformIndexBuffer
{
public:
    PlatformIndexBuffer(const IndexBuffer *indexBuffer);
    ~PlatformIndexBuffer();

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