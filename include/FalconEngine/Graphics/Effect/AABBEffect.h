#pragma once

#include <FalconEngine/Graphics/Common.h>

#include <FalconEngine/Graphics/Renderer/VisualEffect.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectParams.h>

#include <FalconEngine/Math/Matrix4.h>
#include <FalconEngine/Math/Vector3.h>
#include <FalconEngine/Math/Vector4.h>

namespace FalconEngine
{

// @summary Instancing buffer content unit.
#pragma pack(push, 1)
class AABBInstance
{
public:
    Vector4f mColor;
    Matrix4f mModelViewPrjectionTransform;
};
#pragma pack(pop)

// @summary Vertex buffer content unit.
#pragma pack(push, 1)
class AABBVertex
{
public:
    Vector3f mPosition;
};
#pragma pack(pop)

class FALCON_ENGINE_API AABBEffectParams : public VisualEffectParams
{

};

// @summary Implements a aabb bounding box effect using hardware instancing so
// that all bounding box is drawn in one draw call.
class FALCON_ENGINE_API AABBEffect : public VisualEffect
{
    FALCON_ENGINE_EFFECT_DECLARE(AABBEffect);

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit AABBEffect();
    virtual ~AABBEffect();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    std::shared_ptr<VisualEffectInstance>
    CreateInstance(_IN_OUT_ Visual                                  *visual,
                   _IN_     const std::shared_ptr<AABBEffectParams>& params);

    virtual std::shared_ptr<VertexFormat>
    GetVertexFormat() const override;

protected:
    /************************************************************************/
    /* Protected Members                                                    */
    /************************************************************************/
    virtual std::shared_ptr<VertexFormat>
    CreateVertexFormat() const override;
};

}
