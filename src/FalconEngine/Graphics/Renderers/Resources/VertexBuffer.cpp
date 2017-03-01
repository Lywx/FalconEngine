#include <FalconEngine/Graphics/Renderers/Resources/VertexBuffer.h>

namespace FalconEngine
{

VertexBuffer::VertexBuffer(int vertexNum, size_t vertexByteNum, BufferUsage usage) :
    Buffer(vertexNum, vertexByteNum, usage)
{
}

VertexBuffer::VertexBuffer(int vertexNum, int vertexByteNum, BufferUsage usage) :
    Buffer(vertexNum, vertexByteNum, usage)
{
}

VertexBuffer::~VertexBuffer()
{
}

}
