#include <FalconEngine/Graphics/Renderer/Resource/VertexBufferBinding.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
VertexBufferBinding::VertexBufferBinding(std::shared_ptr<VertexBuffer> buffer, int index, int offset, int stride):
    mIndex(index),
    mOffset(offset),
    mStride(stride),
    mBuffer(buffer)
{
}

VertexBufferBinding::~VertexBufferBinding()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
unsigned int
VertexBufferBinding::GetIndex() const
{
    return mIndex;
}

int64_t
VertexBufferBinding::GetOffset() const
{
    return mOffset;
}

void
VertexBufferBinding::SetOffset(int64_t offset)
{
    mOffset = offset;
}

int
VertexBufferBinding::GetStride() const
{
    return mStride;
}

const VertexBuffer *
VertexBufferBinding::GetBuffer() const
{
    return mBuffer.get();
}

std::shared_ptr<VertexBuffer>
VertexBufferBinding::GetBuffer()
{
    return mBuffer;
}

}
