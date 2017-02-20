#include <FalconEngine/Graphics/Renderers/Resources/VertexBuffer.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(VertexBuffer, Buffer);

VertexBuffer::VertexBuffer(int vertexNum, int vertexByteNum, BufferUsage usage) :
    Buffer(vertexNum, vertexByteNum, usage)
{
}

VertexBuffer::~VertexBuffer()
{
}

}
