#pragma once

#include <FalconEngine/GraphicsInclude.h>

#include <map>
#include <vector>

namespace FalconEngine
{

class VertexBuffer;
using VertexBufferSharedPtr = std::shared_ptr<VertexBuffer>;

class VertexBufferBinding
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

}
