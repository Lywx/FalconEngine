#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <vector>

#include <FalconEngine/Graphics/Renderer/Resource/VertexBufferBinding.h>

namespace FalconEngine
{

#pragma warning(disable: 4251)
class FALCON_ENGINE_API VertexGroup
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
#pragma warning(default: 4251)

}
