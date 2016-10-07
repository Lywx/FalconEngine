#pragma once

#include <stdexcept>
#include <memory>

#include <FalconEngine/Graphics/Resources/Buffer.h>

namespace FalconEngine {

class IndexBuffer : public Buffer
{
public:
    IndexBuffer(int indices, int indexSize,
                BufferUsage usage = BufferUsage::STATIC);
    virtual ~IndexBuffer();

    // The offset into the indices is used by the renderer for drawing. The
    // ability to set this is useful when multiple geometric primitives share
    // an index buffer, each primitive using a contiguous set of indices. In
    // this case, SetNumElements and SetOffset will be called dynamically by
    // the application for each such geometric primitive.
    inline void SetOffset(int offset);
    inline int  GetOffset() const;

protected:
    int m_offset;
};

typedef std::shared_ptr<IndexBuffer> IndexBufferPtr;

#include "IndexBuffer.inl"

}
