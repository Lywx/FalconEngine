#pragma once

#include <stdexcept>
#include <memory>

#include <FalconEngine/GraphicsInclude.h>
#include <FalconEngine/Graphics/Renderers/Buffer.h>

namespace FalconEngine
{

using Index = uint32;

class IndexBuffer : public Buffer
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    IndexBuffer(int indexNum, size_t indexChannelByte, BufferUsage usage);
    virtual ~IndexBuffer();

    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
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

inline void IndexBuffer::SetOffset(int offset)
{
    if (offset >= 0)
    {
        m_offset = offset;
    }
    else
    {
        throw std::invalid_argument("The offset must be nonnegative\n");
    }
}

inline int IndexBuffer::GetOffset() const
{
    return m_offset;
}

}
