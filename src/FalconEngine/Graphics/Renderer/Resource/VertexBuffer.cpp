#include <FalconEngine/Graphics/Renderer/Resource/VertexBuffer.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
VertexBuffer::VertexBuffer(int vertexNum, size_t vertexByteNum, BufferUsage usage) :
    Buffer(vertexNum, vertexByteNum, usage)
{
}

VertexBuffer::~VertexBuffer()
{
}

}
