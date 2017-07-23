#pragma once

#include <FalconEngine/Core/Object.h>
#include <FalconEngine/Graphics/Common.h>
#include <FalconEngine/Math/AABB.h>

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

class IndexBuffer;

class VertexBuffer;
class VertexFormat;
class VertexGroup;

// @summary Primitive represents all the resource and metadata that defines a
// geometry primitive that could be rendered into a scene.
#pragma warning(disable: 4251)
class FALCON_ENGINE_API Primitive
{
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
protected:
    explicit Primitive(PrimitiveType type);
    Primitive(PrimitiveType type,
              const std::shared_ptr<VertexFormat>& vertexFormat,
              const std::shared_ptr<VertexGroup>& vertexGroup,
              const std::shared_ptr<IndexBuffer>& indexBuffer);

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
    const AABB *
    GetAABB() const;

    void
    SetAABB(const AABB& aabb);

    /************************************************************************/
    /* Vertex Format Management                                             */
    /************************************************************************/
    // NOTE(Wuxiang): Usually you should never try to access primitive's vertex
    // format because Visual's vertex format might be different from the
    // primitives'. So user might customize the vertex format in the Visual and
    // that stands for the final vertex format.
    const VertexFormat *
    GetVertexFormat() const;

    // NOTE(Wuxiang): You are not allowed to change the vertex format
    // in primitive once it is created.
    std::shared_ptr<const VertexFormat>
    GetVertexFormat();

    /************************************************************************/
    /* Vertex Buffer Management                                             */
    /************************************************************************/
    // NOTE(Wuxiang): Usually you should never try to access primitive's vertex
    // group because Visual's vertex group might be different from the
    // primitives'. So user might customize the vertex group in the Visual and
    // that stands for the final vertex group.
    const VertexGroup *
    GetVertexGroup() const;

    // NOTE(Wuxiang): You are not allowed to change the vertex group
    // in primitive once it is created.
    std::shared_ptr<const VertexGroup>
    GetVertexGroup();

    int
    GetVertexNum() const;

    int
    GetVertexOffset() const;

    void
    SetVertexOffset(int vertexOffset);

    /************************************************************************/
    /* Index Buffer Management                                              */
    /************************************************************************/
    const IndexBuffer *
    GetIndexBuffer() const;

    std::shared_ptr<IndexBuffer>
    GetIndexBuffer();

    int
    GetIndexOffset() const;

    void
    SetIndexOffset(int indexOffset);

    /************************************************************************/
    /* Deep and Shallow Copy                                                */
    /************************************************************************/
    void
    CopyTo(Primitive *rhs);

protected:
    // NOTE(Wuxiang): Notice that both Primitive and Visual class contain vertex
    // format information like class VertexFormat and class VertexGroup. It is
    // necessary and efficient because when loading model you could share the
    // same vertex format and vertex group cross all the mesh you are loading.
    // When drawing with those mesh, you would have the same vertex information
    // stored in the Visual class, shared. When you have special need to attach
    // different buffer into the vertex group you could set the vertex group in
    // in Visual class so that you retain the vertex information in the Primitive
    // class, which is necessary when creating special use vertex format.
    PrimitiveType                   mType;

    std::shared_ptr<AABB>           mAABB;

    std::shared_ptr<VertexFormat>   mVertexFormat;
    std::shared_ptr<VertexGroup>    mVertexGroup;
    int                             mVertexOffset;

    std::shared_ptr<IndexBuffer>    mIndexBuffer;
    int                             mIndexOffset;

};
#pragma warning(default: 4251)

}
