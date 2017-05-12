#pragma once

#include <FalconEngine/Graphics/Renderer/Primitive.h>

namespace FalconEngine
{

class FALCON_ENGINE_ITEM_GRAPHICS PrimitiveLines : public Primitive
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    PrimitiveLines(VertexFormatSharedPtr vertexFormat, VertexGroupSharedPtr vertexGroup, bool vertexStrip = false);
    virtual ~PrimitiveLines();

public:
    bool
    SegmentStrip() const;

    virtual size_t
    GetSegmentNum() const;

protected:
    bool mSegmentStrip;
};
}
