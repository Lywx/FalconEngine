#pragma once

#include <FalconEngine/Graphics/Renderer/Visual.h>
#include <FalconEngine/Graphics/Renderer/VisualTriangles.h>

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
