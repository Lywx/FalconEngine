#pragma once

#include <FalconEngine/Graphics/Renderer/Visual.h>

namespace FalconEngine
{

class VisualLines : public Visual
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    VisualLines(VertexFormatSharedPtr vertexFormat, VertexGroupSharedPtr vertexGroup, bool vertexStrip = false);
    virtual ~VisualLines();

public:
    bool
    IsSegmentStrip() const
    {
        return mSegmentStrip;
    }

    virtual int
    GetSegmentNum() const;

protected:
    bool   mSegmentStrip;
};
}
