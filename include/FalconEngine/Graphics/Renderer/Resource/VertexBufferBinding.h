#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <map>
#include <vector>

namespace FalconEngine
{

class VertexBuffer;
using VertexBufferSharedPtr = std::shared_ptr<VertexBuffer>;

#pragma warning(disable: 4251)
class FALCON_ENGINE_ITEM_GRAPHICS VertexBufferBinding
{
public:
    VertexBufferBinding(VertexBufferSharedPtr buffer, int index, int offset, int stride) :
        mIndex(index),
        mOffset(offset),
        mStride(stride),
        mBuffer(buffer)
    {
    }

    ~VertexBufferBinding()
    {

    }

    int
    GetIndex() const
    {
        return mIndex;
    }

    int
    GetOffset() const
    {
        return mOffset;
    }

    int
    GetStride() const
    {
        return mStride;
    }

    const VertexBuffer *
    GetBuffer() const
    {
        return mBuffer.get();
    }

private:
    int                   mIndex;
    int                   mOffset;
    int                   mStride;
    VertexBufferSharedPtr mBuffer;
};
#pragma warning(default: 4251)

}
