#pragma once

#include <FalconEngine/Graphics/Renderers/Visual.h>

namespace FalconEngine
{

class VisualTriangles : public Visual
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    VisualTriangles();
    VisualTriangles(VertexFormatSharedPtr vertexFormat, int vertexNum, IndexBufferSharedPtr indexBuffer);
    virtual ~VisualTriangles();

public:
    int
    GetTriangleNum() const
    {
        return mTriangleNum;
    }

protected:
    void
    SetPrimitiveNum() override final;

protected:
    size_t mTriangleNum;
};

}
