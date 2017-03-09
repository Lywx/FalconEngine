#pragma once

#include <FalconEngine/GraphicsInclude.h>

#include <FalconEngine/Graphics/Renderer/VisualEffect.h>


namespace FalconEngine
{

class Camera;

class VertexFormat;
using VertexFormatSharedPtr = std::shared_ptr<VertexFormat>;

class BoundingBoxEffect : public VisualEffect
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit BoundingBoxEffect();
    virtual ~BoundingBoxEffect();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    // @summary Add required parameters to the existing visual effect instance.
    void
    CreateInstance(
        _IN_OUT_ VisualEffectInstance *instance,
        _IN_     const Camera *camera) const;

    VertexFormatSharedPtr
    CreateVertexFormat(size_t boundingBoxVertexNum);
};

}
