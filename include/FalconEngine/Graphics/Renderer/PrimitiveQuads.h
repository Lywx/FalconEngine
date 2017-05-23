#pragma once

#include <FalconEngine/Graphics/Renderer/PrimitiveTriangles.h>

namespace FalconEngine
{

class FALCON_ENGINE_API PrimitiveQuads : public PrimitiveTriangles
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    PrimitiveQuads(std::shared_ptr<VertexBuffer> vertexBuffer, std::shared_ptr<IndexBuffer> indexBuffer);
    virtual ~PrimitiveQuads();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    virtual size_t
    GetQuadNum() const;
};

}
