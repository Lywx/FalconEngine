#pragma once

#include <FalconEngine/Graphics/Renderer/Primitive.h>

namespace FalconEngine
{

// @summary Represents line or line strips.
class FALCON_ENGINE_API PrimitiveLines : public Primitive
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    PrimitiveLines(const std::shared_ptr<VertexFormat>& vertexFormat,
                   const std::shared_ptr<VertexGroup>& vertexGroup,
                   const std::shared_ptr<IndexBuffer>& indexBuffer,
                   bool vertexStrip = false);
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
