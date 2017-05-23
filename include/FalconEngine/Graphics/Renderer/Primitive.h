#pragma once

#include <FalconEngine/Graphics/Header.h>
#include <FalconEngine/Core/Object.h>

namespace FalconEngine
{

enum class FALCON_ENGINE_API PrimitiveType
{
    None,
    Point,
    Line,
    LineStrip,
    Triangle,
    TriangleStrip,
    TriangleFan,
    Count,
};

class BoundingBox;

class IndexBuffer;

class VertexBuffer;
class VertexFormat;
class VertexGroup;

#pragma warning(disable: 4251)
class FALCON_ENGINE_API Primitive : public Object
{
    FALCON_ENGINE_RTTI_DECLARE;

protected:
    Primitive(PrimitiveType primitiveType);
    Primitive(PrimitiveType primitiveType, std::shared_ptr<VertexBuffer> vertexBuffer, std::shared_ptr<IndexBuffer> indexBuffer);

public:
    virtual ~Primitive();

public:
    PrimitiveType
    GetPrimitiveType() const;

    const BoundingBox *
    GetBoundingBox() const;

    void
    SetBoundingBox(std::shared_ptr<BoundingBox> boundingBox);

    /************************************************************************/
    /* Vertex Buffer Management                                             */
    /************************************************************************/
    void
    SetVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer);

    const VertexBuffer *
    GetVertexBuffer() const;

    std::shared_ptr<VertexBuffer>
    GetVertexBuffer();

    size_t
    GetVertexNum() const;

    /************************************************************************/
    /* Index Buffer Management                                              */
    /************************************************************************/
    const IndexBuffer *
    GetIndexBuffer() const;

    void
    SetIndexBuffer(std::shared_ptr<IndexBuffer> indexBuffer);

    /************************************************************************/
    /* Deep and Shallow Copy                                                */
    /************************************************************************/
    void
    CopyTo(Primitive *rhs);

protected:
    std::shared_ptr<BoundingBox>  mBoundingBox;
    PrimitiveType                 mPrimitiveType;

    std::shared_ptr<VertexBuffer> mVertexBuffer;
    std::shared_ptr<IndexBuffer>  mIndexBuffer;
};
#pragma warning(default: 4251)

}
