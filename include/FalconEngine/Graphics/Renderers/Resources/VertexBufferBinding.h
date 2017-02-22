#pragma once

#include <FalconEngine/Graphics/GraphicsInclude.h>

#include <map>
#include <vector>

#include <FalconEngine/Graphics/Renderers/Resources/VertexBuffer.h>

namespace FalconEngine
{

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

using VertexBufferBindingVector = std::vector<VertexBufferBinding>;
using VertexBufferBindingTable = std::map<int, VertexBufferBinding>;


}
