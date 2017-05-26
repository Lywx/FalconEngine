#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <vector>

#include <FalconEngine/Graphics/Renderer/Resource/VertexBufferBinding.h>

namespace FalconEngine
{

// @summary Vertex group represents a collection of vertex buffer binding. It
// has all the information about vertex buffers used in any shaders.
#pragma warning(disable: 4251)
class FALCON_ENGINE_API VertexGroup
{
public:
    VertexGroup();
    virtual ~VertexGroup();

public:
    void
    ClearVertexBuffer();

    const VertexBuffer *
    GetVertexBuffer(int bindingIndex) const;

    std::shared_ptr<VertexBuffer>
    GetVertexBuffer(int bindingIndex);

    void
    SetVertexBuffer(int bindingIndex, std::shared_ptr<VertexBuffer> vertexBuffer, int offset, int stride);

public:
    std::map<int, VertexBufferBinding> mVertexBufferTable;
};
#pragma warning(default: 4251)

}
