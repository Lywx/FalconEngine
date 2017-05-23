#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <map>
#include <vector>

namespace FalconEngine
{

class VertexBuffer;

// @summary Buffer binding is the basic unit of meta-vertex-buffer data. Buffer binding
// represents an OpenGL vertex buffer binding point.
// @remark Buffer binding is copyable. This is how would you share vertex buffer
// information.
#pragma warning(disable: 4251)
class FALCON_ENGINE_API VertexBufferBinding
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    VertexBufferBinding(std::shared_ptr<VertexBuffer> buffer, int index, int offset, int stride);
    VertexBufferBinding(const VertexBufferBinding& rhs) = default;
    ~VertexBufferBinding();

    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    // @summary Vertex buffer binding index.
    int
    GetIndex() const;

    // @summary Vertex buffer offset.
    int
    GetOffset() const;

    // @summary Vertex buffer stride.
    int
    GetStride() const;

    // @summary Vertex buffer pointer.
    const VertexBuffer *
    GetBuffer() const;

private:
    int                           mIndex;
    int                           mOffset;
    int                           mStride;
    std::shared_ptr<VertexBuffer> mBuffer;
};
#pragma warning(default: 4251)

}
