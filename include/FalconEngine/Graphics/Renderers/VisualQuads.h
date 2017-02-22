#pragma once

#include <FalconEngine/Graphics/Renderers/Visual.h>
#include <FalconEngine/Graphics/Renderers/VisualTriangles.h>

namespace FalconEngine
{

class VisualQuads : public VisualTriangles
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    VisualQuads(VertexFormatSharedPtr vertexFormat, VertexGroupSharedPtr vertexGroup);
    virtual ~VisualQuads();

public:
};

}
