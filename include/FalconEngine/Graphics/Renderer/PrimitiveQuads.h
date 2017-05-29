#pragma once

#include <FalconEngine/Graphics/Renderer/PrimitiveTriangles.h>

namespace FalconEngine
{

class FALCON_ENGINE_API PrimitiveQuads : public PrimitiveTriangles
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    PrimitiveQuads(std::shared_ptr<VertexFormat> vertexFormat,
                   std::shared_ptr<VertexGroup>  vertexGroup,
                   std::shared_ptr<IndexBuffer>  indexBuffer);
    virtual ~PrimitiveQuads();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    virtual size_t
    GetQuadNum() const;
};

}
