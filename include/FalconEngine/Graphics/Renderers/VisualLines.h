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
    VisualLines(VertexFormatSharedPtr vertexFormat, int vertexNum, bool vertexStrip = false);
    virtual ~VisualLines();

public:
    int
    GetSegmentNum() const
    {
        return mSegmentNum;
    }

    bool
    IsSegmentStrip() const
    {
        return mSegmentStrip;
    }

protected:
    void
    SetPrimitiveNum() override final;

protected:
    size_t mSegmentNum;
    bool   mSegmentStrip;
};
}
