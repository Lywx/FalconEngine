#pragma once

#include <FalconEngine/Graphics/Renderer/Primitive.h>

namespace FalconEngine
{

class PrimitiveTriangles : public Primitive
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PrimitiveTriangles(VertexFormatSharedPtr vertexFormat);
    PrimitiveTriangles(VertexFormatSharedPtr vertexFormat, VertexGroupSharedPtr vertexGroup, IndexBufferSharedPtr indexBuffer);
    virtual ~PrimitiveTriangles();

public:
    virtual size_t
    GetTriangleNum() const;
};

}
