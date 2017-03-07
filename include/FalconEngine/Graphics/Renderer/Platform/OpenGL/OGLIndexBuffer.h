#pragma once

#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLInclude.h>
#include <FalconEngine/Graphics/Renderer/Resource/IndexBuffer.h>

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