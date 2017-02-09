#pragma once

#include <FalconEngine/Graphics/Renderers/Visual.h>

namespace FalconEngine
{

class VisualLines : public Visual
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    VisualLines(VertexBufferSharedPtr vertexBuffer, bool lineStrip = false);
    virtual ~VisualLines();

public:
    size_t mSegmentNum;
    bool   mSegmentStrip;
};
}
