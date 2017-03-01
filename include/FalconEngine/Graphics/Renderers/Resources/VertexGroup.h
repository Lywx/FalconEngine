#pragma once

#include <FalconEngine/GraphicsInclude.h>

#include <vector>

#include <FalconEngine/Graphics/Renderers/Resources/VertexBufferBinding.h>

namespace FalconEngine
{

class VertexGroup
{
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
    SetVertexBuffer(int bindingIndex, VertexBufferSharedPtr vertexBuffer, int offset, int stride);

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
    std::map<int, VertexBufferBinding> mVertexBufferTable;

private:
    int mVertexNum;

};

}
