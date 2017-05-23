#pragma once

#include <FalconEngine/Graphics/Renderer/Primitive.h>

namespace FalconEngine
{

// @summary Represents line or line strips.
class FALCON_ENGINE_API PrimitiveLines : public Primitive
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    PrimitiveLines(std::shared_ptr<VertexBuffer> vertexBuffer, bool vertexStrip);
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
