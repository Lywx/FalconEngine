#include <FalconEngine/Graphics/Renderer/Resource/VertexBuffer.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
VertexBuffer::VertexBuffer(int vertexNum, size_t vertexSize, BufferStorageMode storageMode, BufferUsage usage) :
    Buffer(vertexNum, vertexSize, storageMode, BufferType::VertexBuffer, usage)
{
}

VertexBuffer::~VertexBuffer()
{
}

}
