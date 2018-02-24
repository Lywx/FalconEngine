#pragma once

#include <FalconEngine/Core/Macro.h>

#include <FalconEngine/Graphics/Renderer/VisualEffect.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectParams.h>
#include <FalconEngine/Math/Color.h>

namespace FalconEngine
{

namespace Detail
{

FALCON_ENGINE_STRUCT_BEGIN SkyBufferData
{
    Matrix4f mViewProjectionTransform;
};
FALCON_ENGINE_STRUCT_END

}

class Visual;
class Mesh;
class Node;

class FALCON_ENGINE_API SkyEffectParams : public VisualEffectParams
{
};

class FALCON_ENGINE_API SkyEffect : public VisualEffect
{
public:
    FALCON_ENGINE_EFFECT_DECLARE(SkyEffect);

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    SkyEffect();
    virtual ~SkyEffect();

public:
    void
    CreateInstance(
        _IN_OUT_ Node *node,
        _IN_     const std::shared_ptr<SkyEffectParams>& params);

protected:
    /************************************************************************/
    /* Protected Members                                                    */
    /************************************************************************/
    void
    InitializeInstance(
        _IN_OUT_ VisualEffectInstance *instance,
        _IN_     const std::shared_ptr<Material>& material,
        _IN_     const std::shared_ptr<SkyEffectParams>& params) const;
};

}
