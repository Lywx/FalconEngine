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
class FALCON_ENGINE_API Primitive
{
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
protected:
    Primitive(PrimitiveType primitiveType);
    Primitive(PrimitiveType primitiveType, std::shared_ptr<VertexFormat> vertexFormat, std::shared_ptr<VertexGroup> vertexGroup, std::shared_ptr<IndexBuffer> indexBuffer);

public:
    virtual ~Primitive();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    PrimitiveType
    GetPrimitiveType() const;

    /************************************************************************/
    /* Bounding Box Management                                              */
    /************************************************************************/
    // NOTE(Wuxiang): The decision to put bounding box inside primitive is
    // natural. I don't see changes that it would change in the future.
    const BoundingBox *
    GetBoundingBox() const;

    void
    SetBoundingBox(std::shared_ptr<BoundingBox> boundingBox);

    /************************************************************************/
    /* Vertex Buffer Management                                             */
    /************************************************************************/
    const VertexFormat *
    GetVertexFormat() const;

    std::shared_ptr<VertexFormat>
    GetVertexFormat();

    const VertexGroup *
    GetVertexGroup() const;

    std::shared_ptr<VertexGroup>
    GetVertexGroup();

    size_t
    GetVertexNum() const;

    /************************************************************************/
    /* Index Buffer Management                                              */
    /************************************************************************/
    const IndexBuffer *
    GetIndexBuffer() const;

    std::shared_ptr<IndexBuffer>
    GetIndexBuffer();

    /************************************************************************/
    /* Deep and Shallow Copy                                                */
    /************************************************************************/
    void
    CopyTo(Primitive *rhs);

protected:
    PrimitiveType                 mPrimitiveType;

    // NOTE(Wuxiang): Notice that both Primitive and Visual class contain vertex
    // format information like class VertexFormat and class VertexGroup. It is
    // necessary and efficient because when loading model you could share the
    // same vertex format and vertex group cross all the mesh you are loading.
    // When drawing with those mesh, you would have the same vertex information
    // stored in the Visual class, shared. When you have special need to attach
    // different buffer into the vertex group you could set the vertex group in
    // in Visual class so that you retain the vertex information in the Primitive
    // class, which is necessary when creating special use vertex format.
    std::shared_ptr<BoundingBox>  mBoundingBox;
    std::shared_ptr<VertexFormat> mVertexFormat;
    std::shared_ptr<VertexGroup>  mVertexGroup;
    std::shared_ptr<IndexBuffer>  mIndexBuffer;
};
#pragma warning(default: 4251)

}
