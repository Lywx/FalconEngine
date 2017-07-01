#include <FalconEngine/Graphics/Renderer/Resource/IndexBuffer.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
IndexBuffer::IndexBuffer(int indexNum, IndexType indexType, BufferStorageMode storageMode, BufferUsage usage) :
    // The index buffer doesn't need the vertex array information about index
    // channel dimension. So we pass 1 here.
    Buffer(indexNum,
           indexType == IndexType::UnsignedShort
           ? sizeof(unsigned short)
           : sizeof(unsigned int),
           storageMode, BufferType::IndexBuffer, usage),
    mType(indexType)
{
}

IndexBuffer::~IndexBuffer()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
IndexType
IndexBuffer::GetIndexType() const
{
    return mType;
}

}
