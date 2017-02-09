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
    VisualTriangles(VertexBufferSharedPtr vertexBuffer, IndexBufferSharedPtr indexBuffer);
    virtual ~VisualTriangles();

public:
    size_t mTriangleNum;
};

}
