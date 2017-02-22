#pragma once

#include <FalconEngine/Graphics/GraphicsInclude.h>
#include <FalconEngine/Graphics/Renderers/Resources/VertexBufferBinding.h>

namespace FalconEngine
{

class VertexGroup : public Object
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    VertexGroup();
    virtual ~VertexGroup();

public:
    void
    ClearVertexBuffer()
    {
        mVertexBufferTable.clear();
    }

    bool
    ContainVertexBuffer(int bindingIndex, VertexBufferSharedPtr vertexBuffer)
    {
        return mVertexBufferTable.find(bindingIndex) != mVertexBufferTable.end()
               && mVertexBufferTable.at(bindingIndex).GetBuffer() == vertexBuffer.get();
    }

    void
    SetVertexBuffer(int bindingIndex, VertexBufferSharedPtr vertexBuffer, int offset, int stride)
    {
        mVertexBufferTable[bindingIndex] = VertexBufferBinding(vertexBuffer, bindingIndex, offset, stride);
    }

    int
    GetVertexNum() const
    {
        return mVertexNum;
    }

    void
    SetVertexNum(int vertexNum)
    {
        mVertexNum = vertexNum;
    }

public:
    VertexBufferBindingTable mVertexBufferTable;

private:
    int mVertexNum;

};

using VertexGroupSharedPtr = std::shared_ptr<VertexGroup>;

}
