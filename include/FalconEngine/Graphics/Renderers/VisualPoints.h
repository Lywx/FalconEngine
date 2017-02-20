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
    VisualPoints(VertexFormatSharedPtr vertexFormat, int vertexNum);
    virtual ~VisualPoints();

public:
    int
    GetPointNum() const;

protected:
    void
    SetPrimitiveNum() override final;

protected:
    size_t mPointNum;
};
}
