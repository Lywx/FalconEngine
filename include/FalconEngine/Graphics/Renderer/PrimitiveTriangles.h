#pragma once

#include <FalconEngine/Graphics/Renderer/Primitive.h>

namespace FalconEngine
{

// @summary Represents triangle primitives, which includes triangle
// strips, triangle fans.
class FALCON_ENGINE_API PrimitiveTriangles : public Primitive
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    PrimitiveTriangles(std::shared_ptr<VertexFormat> vertexFormat,
                       std::shared_ptr<VertexGroup>  vertexGroup,
                       std::shared_ptr<IndexBuffer>  indexBuffer);

    // @remark Allow derived class to pass primitive type themselves.
    PrimitiveTriangles(PrimitiveType                 primitiveType,
                       std::shared_ptr<VertexFormat> vertexFormat,
                       std::shared_ptr<VertexGroup>  vertexGroup,
                       std::shared_ptr<IndexBuffer>  indexBuffer);
    virtual ~PrimitiveTriangles();

public:
    virtual size_t
    GetTriangleNum() const;
};

}
