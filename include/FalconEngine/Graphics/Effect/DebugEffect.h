#pragma once

#include <FalconEngine/Core/Macro.h>

#include <functional>
#include <map>
#include <queue>

#include <FalconEngine/Graphics/Renderer/VisualEffect.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectParams.h>
#include <FalconEngine/Graphics/Renderer/Resource/UniformBufferManual.h>
#include <FalconEngine/Math/Color.h>
#include <FalconEngine/Math/Vector2.h>

namespace FalconEngine
{

namespace Detail
{
#pragma pack(push, 1)
struct FALCON_ENGINE_API DebugVertexData
{
    Vector2f mPosition;
    Vector4f mColor;
};
#pragma pack(pop)

FALCON_ENGINE_STRUCT_BEGIN DebugTransformBufferData
{
    Matrix4f mViewProjectionTransform;
};
FALCON_ENGINE_STRUCT_END
}

class Visual;
class Mesh;
class Node;

FALCON_ENGINE_CLASS_BEGIN DebugEffectParams :
public VisualEffectParams
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    DebugEffectParams();

public:
    const Camera *mCamera;
};

class FALCON_ENGINE_API DebugEffect : public VisualEffect
{
    FALCON_ENGINE_EFFECT_DECLARE(DebugEffect);

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit DebugEffect(bool depthTestEnabled);
    virtual ~DebugEffect();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    CreateInstance(_IN_OUT_ Visual                                   *visual,
                   _IN_     const std::shared_ptr<DebugEffectParams>& params);

protected:
    /************************************************************************/
    /* Protected Members                                                    */
    /************************************************************************/
    void
    InitializeInstance(
        _IN_OUT_ VisualEffectInstance              *instance,
        _IN_     std::shared_ptr<DebugEffectParams> params) const;
};
FALCON_ENGINE_CLASS_END
}
