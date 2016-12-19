#include <FalconEngine/Graphics/Renderers/VertexBuffer.h>

namespace FalconEngine
{

FALCON_ENGINE_IMPLEMENT_RTTI(VertexBuffer, Object);

VertexBuffer::VertexBuffer(int vertexNum, int vertexChannel, size_t vertexChannelByte, BufferUsage usage)
    : Buffer(vertexNum, vertexChannel, vertexChannelByte, usage)
{
}

VertexBuffer::~VertexBuffer()
{
    // TODO(Wuxiang): Delete platform vertex buffer to release gpu memory
}

}
