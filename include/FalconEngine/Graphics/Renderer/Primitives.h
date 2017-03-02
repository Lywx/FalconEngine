#pragma once

#include <FalconEngine/Graphics/Scene/Spatial.h>

namespace FalconEngine
{

enum class PrimitiveType
{
    None,
    Point,
    Line,
    LineStrip,
    Triangle,
    Count,
};

class IndexBuffer;
using IndexBufferSharedPtr = std::shared_ptr<IndexBuffer>;

class VertexBuffer;
using VertexBufferSharedPtr = std::shared_ptr<VertexBuffer>;

class VertexFormat;
using VertexFormatSharedPtr = std::shared_ptr<VertexFormat>;

class VertexGroup;
using VertexGroupSharedPtr = std::shared_ptr<VertexGroup>;

class Primitives : public Spatial
{
    FALCON_ENGINE_RTTI_DECLARE;

protected:
    Primitives(PrimitiveType primitiveType, VertexFormatSharedPtr vertexFormat);
    Primitives(PrimitiveType primitiveType, VertexFormatSharedPtr vertexFormat, VertexGroupSharedPtr vertexGroup, IndexBufferSharedPtr indexBuffer);
public:
    virtual ~Primitives();

public:
    PrimitiveType
    GetPrimitiveType() const
    {
        return mPrimitiveType;
    }

    /************************************************************************/
    /* Vertex Buffer Management                                             */
    /************************************************************************/
    void
    SetVertexBuffer(int bindingIndex, VertexBufferSharedPtr vertexBuffer, int offset, int stride);

    const VertexGroup *
    GetVertexGroup() const;

    int
    GetVertexNum() const;

    const VertexFormat *
    GetVertexFormat() const
    {
        return mVertexFormat.get();
    }

    void
    SetVertexFormat(VertexFormatSharedPtr vertexFormat)
    {
        mVertexFormat = vertexFormat;
    }

    const IndexBuffer *
    GetIndexBuffer() const
    {
        return mIndexBuffer.get();
    }

    void
    SetIndexBuffer(IndexBufferSharedPtr indexBuffer)
    {
        mIndexBuffer = indexBuffer;
    }

protected:
    PrimitiveType         mPrimitiveType;
    VertexGroupSharedPtr  mVertexGroup;
    VertexFormatSharedPtr mVertexFormat;
    IndexBufferSharedPtr  mIndexBuffer;
};

}
