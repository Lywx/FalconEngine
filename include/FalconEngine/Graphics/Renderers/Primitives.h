#pragma once

#include <FalconEngine/Graphics/Renderers/VisualEffectInstance.h>
#include <FalconEngine/Graphics/Renderers/Resources/IndexBuffer.h>
#include <FalconEngine/Graphics/Renderers/Resources/VertexGroup.h>
#include <FalconEngine/Graphics/Renderers/Resources/VertexFormat.h>
#include <FalconEngine/Graphics/Scenes/Spatial.h>

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

    int
    GetVertexNum() const
    {
        return mVertexGroup->GetVertexNum();
    }

    void
    SetVertexNum(int vertexNum) const
    {
        mVertexGroup->SetVertexNum(vertexNum);
    }

    void
    SetVertexBuffer(int bindingIndex, VertexBufferSharedPtr vertexBuffer, int offset, int stride);

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
