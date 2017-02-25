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
    explicit VisualPoints(VertexFormatSharedPtr vertexFormat);
    VisualPoints(VertexFormatSharedPtr vertexFormat, VertexGroupSharedPtr vertexGroup);
    virtual ~VisualPoints();

public:
    virtual int
    GetPointNum() const;
};
}
