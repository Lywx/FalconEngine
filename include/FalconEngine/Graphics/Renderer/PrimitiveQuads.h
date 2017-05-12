#pragma once

#include <FalconEngine/Graphics/Renderer/PrimitiveTriangles.h>

namespace FalconEngine
{

class FALCON_ENGINE_ITEM_GRAPHICS PrimitiveQuads : public PrimitiveTriangles
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    PrimitiveQuads(VertexFormatSharedPtr vertexFormat, VertexGroupSharedPtr vertexGroup);
    virtual ~PrimitiveQuads();
};

}
