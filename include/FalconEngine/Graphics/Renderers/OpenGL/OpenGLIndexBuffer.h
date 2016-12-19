#pragma once

#include <FalconEngine/Graphics/Renderers/IndexBuffer.h>
#include <FalconEngine/Graphics/Renderers/OpenGL/OpenGLInclude.h>

namespace FalconEngine
{

class OpenGLIndexBuffer
{
public:
    // TODO
    OpenGLIndexBuffer(Renderer *renderer, const IndexBuffer *indexBuffer);
    ~OpenGLIndexBuffer();

    // Buffer operations.
    void Enable(Renderer *renderer);
    void Disable(Renderer *renderer);
    void *Lock(Buffer::Locking mode);
    void Unlock();

private:
    GLuint mBuffer;
};

}