#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <FalconEngine/Graphics/Renderer/VisualEffect.h>

#include <FalconEngine/Math/Matrix4.h>
#include <FalconEngine/Math/Vector3.h>
#include <FalconEngine/Math/Vector4.h>

namespace FalconEngine
{

#pragma pack(push, 1)
class BoundingBoxInstance
{
public:
    Vector4f mColor;
    Matrix4f mModelViewPrjectionTransform;
};
#pragma pack(pop)

#pragma pack(push, 1)
class BoundingBoxVertex
{
public:
    Vector3f mPosition;
};
#pragma pack(pop)


class Camera;

class VertexFormat;
using VertexFormatSharedPtr = std::shared_ptr<VertexFormat>;

class FALCON_ENGINE_API AABBBoundingBoxEffect : public VisualEffect
{
    FALCON_ENGINE_RTTI_DECLARE;

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
    // @summary Add required parameters to the existing visual effect instance.
    void
    CreateInstance(
        _IN_OUT_ VisualEffectInstance *instance,
        _IN_     const Camera *camera) const;

    VertexFormatSharedPtr
    CreateVertexFormat();
};

}
