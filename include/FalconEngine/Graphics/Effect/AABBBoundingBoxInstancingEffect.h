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

class FALCON_ENGINE_API AABBBoundingBoxInstancingEffect : public VisualEffect
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit AABBBoundingBoxInstancingEffect();
    virtual ~AABBBoundingBoxInstancingEffect();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    // @summary Add required parameters to the existing visual effect instance.
    void
    CreateInstance(
        _IN_OUT_ VisualEffectInstance *instance,
        _IN_     const Camera *camera) const;

    virtual std::shared_ptr<VertexFormat>
    GetVertexFormat() const override;
};

}
