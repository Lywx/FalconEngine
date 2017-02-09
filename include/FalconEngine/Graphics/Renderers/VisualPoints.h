#pragma once

#include <FalconEngine/Graphics/Renderers/Visual.h>

namespace FalconEngine
{

class VisualPoints : public Visual
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    VisualPoints(VertexBufferSharedPtr vertexBuffer);
    virtual ~VisualPoints();

public:
    size_t mPointNum;
};
}
