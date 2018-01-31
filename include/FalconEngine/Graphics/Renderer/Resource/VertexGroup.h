#pragma once

#include <FalconEngine/Core/Macro.h>

#include <algorithm>
#include <memory>
#include <vector>

#include <FalconEngine/Graphics/Renderer/Resource/VertexBufferBinding.h>

namespace FalconEngine
{

// @summary Vertex group represents a collection of vertex buffer binding. It
// has all the information about vertex buffers used in any shaders.
//
// @remark For any vertex group there is only one unique vertex format parameter
// could support that vertex group. But inverse proposition is not true because
// binding index could be used to bind different vertex buffers.
#pragma warning(disable: 4251)
class FALCON_ENGINE_API VertexGroup
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    VertexGroup();
    virtual ~VertexGroup();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    int
    GetVertexNum() const;

    void
    ClearVertexBuffer();

    const VertexBuffer *
    GetVertexBuffer(unsigned int bindingIndex) const;

    std::shared_ptr<VertexBuffer>
    GetVertexBuffer(unsigned int bindingIndex);

    void
    SetVertexBuffer(unsigned int                         bindingIndex,
                    const std::shared_ptr<VertexBuffer>& vertexBuffer,
                    int64_t                              offset,
                    int                                  stride);

    std::shared_ptr<VertexBufferBinding>
    FindVertexBufferBinding(const VertexBuffer *vertexBuffer) const;

    std::shared_ptr<VertexBufferBinding>
    GetVertexBufferBinding(unsigned int bindingIndex) const;

    auto
    GetVertexBufferBindingBegin() const
    {
        return mVertexBufferBindingTable.cbegin();
    }

    auto
    GetVertexBufferBindingEnd() const
    {
        return mVertexBufferBindingTable.cend();
    }

    auto
    GetVertexBufferBindingBegin()
    {
        return mVertexBufferBindingTable.begin();
    }

    auto
    GetVertexBufferBindingEnd()
    {
        return mVertexBufferBindingTable.end();
    }

    bool
    IsVertexBufferBindingAvailable(unsigned int bindingIndex) const;

private:
    void
    CheckVertexBufferBindingValid(unsigned int bindingIndex) const;

private:
    std::map<unsigned int, std::shared_ptr<VertexBufferBinding>> mVertexBufferBindingTable;
};
#pragma warning(default: 4251)

}
