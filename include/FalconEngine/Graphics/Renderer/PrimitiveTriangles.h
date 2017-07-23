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
    // @remark Allow derived class to pass extra primitive type to fine-tune
    // primitive behavior.
    PrimitiveTriangles(const std::shared_ptr<VertexFormat>& vertexFormat,
                       const std::shared_ptr<VertexGroup>& vertexGroup,
                       const std::shared_ptr<IndexBuffer>& indexBuffer,
                       PrimitiveType type = PrimitiveType::Triangle);
    virtual ~PrimitiveTriangles();

public:
    virtual size_t
    GetTriangleNum() const;
};

}
