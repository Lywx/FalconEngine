#pragma once

#include <FalconEngine/GraphicsInclude.h>

#include <vector>

#include <FalconEngine/Graphics/Renderer/Resources/VertexBufferBinding.h>

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

    size_t
    GetVertexNum() const;

    void
    SetVertexBuffer(int bindingIndex, VertexBufferSharedPtr vertexBuffer, int offset, int stride);

public:
    std::map<int, VertexBufferBinding> mVertexBufferTable;

};

}
