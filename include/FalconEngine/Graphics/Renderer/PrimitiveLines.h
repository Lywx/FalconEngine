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
    PrimitiveLines(std::shared_ptr<VertexFormat> vertexFormat,
                   std::shared_ptr<VertexGroup>  vertexGroup,
                   std::shared_ptr<IndexBuffer>  indexBuffer,
                   bool                          vertexStrip);
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
