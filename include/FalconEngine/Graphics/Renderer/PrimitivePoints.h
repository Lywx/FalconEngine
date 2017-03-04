#pragma once

#include <FalconEngine/Graphics/Renderer/Primitive.h>

namespace FalconEngine
{

class PrimitivePoints : public Primitive
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PrimitivePoints(VertexFormatSharedPtr vertexFormat);
    PrimitivePoints(VertexFormatSharedPtr vertexFormat, VertexGroupSharedPtr vertexGroup);
    virtual ~PrimitivePoints();

public:
    virtual size_t
    GetPointNum() const;
};
}
