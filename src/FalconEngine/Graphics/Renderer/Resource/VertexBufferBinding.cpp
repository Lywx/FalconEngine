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
int
VertexBufferBinding::GetIndex() const
{
    return mIndex;
}

int
VertexBufferBinding::GetOffset() const
{
    return mOffset;
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
}
