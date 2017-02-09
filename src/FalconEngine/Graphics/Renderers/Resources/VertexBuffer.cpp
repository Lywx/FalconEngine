#include <FalconEngine/Graphics/Renderers/Resources/VertexBuffer.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(VertexBuffer, Object);

VertexBuffer::VertexBuffer(unsigned char *vertexData, int vertexNum, int vertexByteNum, BufferUsage usage)
    : Buffer(vertexData, vertexNum, vertexByteNum, usage)
{
}

VertexBuffer::~VertexBuffer()
{
}

}
