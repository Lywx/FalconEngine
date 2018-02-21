#include <FalconEngine/Graphics/Renderer/Resource/VertexBufferBinding.h>
#include <utility>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
VertexBufferBinding::VertexBufferBinding(
    std::shared_ptr<VertexBuffer> buffer,
    unsigned int index,
    int64_t offset,
    int stride,
    const VertexGroup *group) :
    mIndex(index),
    mOffset(offset),
    mStride(stride),
    mBuffer(std::move(buffer)),
    mGroup(group)
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

const VertexGroup *
VertexBufferBinding::GetGroup() const
{
    return mGroup;
}
}
