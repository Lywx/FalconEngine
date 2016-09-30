#include <FalconEngine/Graphics/Resources/VertexBuffer.h>

namespace FalconEngine {

FALCON_ENGINE_IMPLEMENT_RTTI(VertexBuffer, Object);

VertexBuffer::VertexBuffer(int vertices, int vertexSize, BufferUsage usage)
    : Buffer(vertices, vertexSize, usage)
{
}

VertexBuffer::~VertexBuffer()
{
    // TODO
    // Renderer::UnbindAll(this);
}

}
