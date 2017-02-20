#include <FalconEngine/Graphics/Renderers/Resources/IndexBuffer.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(IndexBuffer, Buffer);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
IndexBuffer::IndexBuffer(int indexNum, IndexType indexType, BufferUsage usage) :
    // The index buffer doesn't need the vertex array information about index
    // channel dimension. So we pass 1 here.
    Buffer(indexNum, indexType == IndexType::UnsignedShort
           ? sizeof(unsigned short)
           : sizeof(unsigned int), usage),
    mOffset(0),
    mType(indexType)
{
}

IndexBuffer::~IndexBuffer()
{
}

}
