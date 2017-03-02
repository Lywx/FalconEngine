#include <FalconEngine/Graphics/Renderer/Resources/VertexBuffer.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
VertexBuffer::VertexBuffer(size_t vertexNum, size_t vertexByteNum, BufferUsage usage) :
    Buffer(vertexNum, vertexByteNum, usage)
{
}

VertexBuffer::~VertexBuffer()
{
}

}
