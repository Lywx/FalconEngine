#include <FalconEngine/Graphics/Renderer/Resource/VertexBuffer.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
VertexBuffer::VertexBuffer(int vertexNum, size_t vertexByteNum, BufferStorageMode storageMode, BufferUsage usage) :
    Buffer(vertexNum, vertexByteNum, storageMode, BufferType::VertexBuffer, usage)
{
}

VertexBuffer::~VertexBuffer()
{
}

}
