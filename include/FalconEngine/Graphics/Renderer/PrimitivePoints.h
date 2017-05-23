#pragma once

#include <FalconEngine/Graphics/Renderer/Primitive.h>

namespace FalconEngine
{

class FALCON_ENGINE_API PrimitivePoints : public Primitive
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PrimitivePoints(std::shared_ptr<VertexBuffer> vertexBuffer);
    virtual ~PrimitivePoints();

public:
    virtual size_t
    GetPointNum() const;
};
}
