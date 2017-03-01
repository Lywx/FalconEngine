#pragma once

#include <FalconEngine/Graphics/Renderer/Visual.h>

namespace FalconEngine
{

class VisualTriangles : public Visual
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit VisualTriangles(VertexFormatSharedPtr vertexFormat);
    VisualTriangles(VertexFormatSharedPtr vertexFormat, VertexGroupSharedPtr vertexGroup, IndexBufferSharedPtr indexBuffer);
    virtual ~VisualTriangles();

public:
    virtual int
    GetTriangleNum() const;
};

}
