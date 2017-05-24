#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <FalconEngine/Graphics/Renderer/VisualEffect.h>

#include <FalconEngine/Math/Matrix4.h>
#include <FalconEngine/Math/Vector3.h>
#include <FalconEngine/Math/Vector4.h>

namespace FalconEngine
{

#pragma pack(push, 1)
class AABBBoundingBoxInstance
{
public:
    Vector4f mColor;
    Matrix4f mModelViewPrjectionTransform;
};
#pragma pack(pop)

#pragma pack(push, 1)
class AABBBoundingBoxVertex
{
public:
    Vector3f mPosition;
};
#pragma pack(pop)


class Camera;

class VertexFormat;

// @summary Implements a aabb bounding box effect using hardware instancing so
// that all bounding box is drawn in one draw call.
class FALCON_ENGINE_API AABBBoundingBoxEffect : public VisualEffect
{
    FALCON_ENGINE_EFFECT_DECLARE(AABBBoundingBoxEffect);

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit AABBBoundingBoxEffect();
    virtual ~AABBBoundingBoxEffect();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    std::shared_ptr<VisualEffectInstance>
    CreateInstance(Visual *visual, std::shared_ptr<VertexBuffer> instanceBuffer) const;

protected:
    virtual std::shared_ptr<VisualEffectInstance>
    CreateSetInstance(Visual *visual) const override;

    virtual std::shared_ptr<VertexFormat>
    GetVertexFormat() const override;
};

}
