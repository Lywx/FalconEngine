#pragma once

#include <FalconEngine/Graphics/Renderer/Primitive.h>

namespace FalconEngine
{

class FALCON_ENGINE_API PrimitivePoints : public Primitive
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    PrimitivePoints(std::shared_ptr<VertexFormat> vertexFormat,
                    std::shared_ptr<VertexGroup>  vertexGroup);
    virtual ~PrimitivePoints();

public:
    virtual size_t
    GetPointNum() const;
};
}
