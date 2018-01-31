#pragma once

#include <FalconEngine/Core/Macro.h>

#include <FalconEngine/Graphics/Renderer/VisualEffect.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectParams.h>

#include <FalconEngine/Math/Matrix4.h>
#include <FalconEngine/Math/Vector3.h>
#include <FalconEngine/Math/Vector4.h>

namespace FalconEngine
{

// @summary Instancing buffer content unit.
#pragma pack(push, 1)
class AabbInstance
{
public:
    Vector4f mColor;
    Matrix4f mModelViewPrjectionTransform;
};
#pragma pack(pop)

// @summary Vertex buffer content unit.
#pragma pack(push, 1)
class AabbVertex
{
public:
    Vector3f mPosition;
};
#pragma pack(pop)

class FALCON_ENGINE_API AabbEffectParams : public VisualEffectParams
{

};

// @summary Implements a aabb bounding box effect using hardware instancing so
// that all bounding box is drawn in one draw call.
class FALCON_ENGINE_API AabbEffect : public VisualEffect
{
    FALCON_ENGINE_EFFECT_DECLARE(AabbEffect);

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit AabbEffect();
    virtual ~AabbEffect();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    std::shared_ptr<VisualEffectInstance>
    CreateInstance(_IN_OUT_ Visual                                  *visual,
                   _IN_     const std::shared_ptr<AabbEffectParams>& params);

    virtual std::shared_ptr<VertexFormat>
    GetVertexFormatSp() const override;

protected:
    /************************************************************************/
    /* Protected Members                                                    */
    /************************************************************************/
    virtual std::shared_ptr<VertexFormat>
    CreateVertexFormat() const override;
};

}
