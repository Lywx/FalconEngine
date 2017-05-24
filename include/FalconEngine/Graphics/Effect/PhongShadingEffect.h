#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <FalconEngine/Graphics/Renderer/VisualEffect.h>

namespace FalconEngine
{

class Light;
class Material;
class Mesh;
class Node;

class Visual;
class VisualEffectInstance;

class FALCON_ENGINE_API PhongShadingEffect : public VisualEffect
{
    FALCON_ENGINE_EFFECT_DECLARE(PhongShadingEffect);

public:
    static int PointLightNumMax;
    static int SpotLightNumMax;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    PhongShadingEffect();
    virtual ~PhongShadingEffect();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    // @summary Add required parameters to the existing visual effect instance.
    // @remark Need a shared_ptr of visual effect of its own because this method
    // need to create visual effect instance for all visual whose rooted to given
    // node. Creation of visual effect instance need this shared_ptr. But the
    // shared_ptr has to be used carefully for itself because it manage the
    // lifetime of the object. You won't want to store a shared_ptr of itself
    // because it would cause the destructor to call twice.
    void
    CreateInstance(_IN_OUT_ Node                             *node,
                   _IN_     const Light&                      directionalLight,
                   _IN_     const std::vector<const Light *>& pointLightList,
                   _IN_     const std::vector<const Light *>& spotLightList) const;

protected:
    virtual std::shared_ptr<VisualEffectInstance>
    CreateSetInstance(Visual *visual) const override;

    // @summary Add required parameters to the existing visual effect instance.
    void
    InitializeInstance(
        _IN_OUT_ VisualEffectInstance             *visualEffectInstance,
        _IN_     const Material&                   material,
        _IN_     const Light&                      directionalLight,
        _IN_     const std::vector<const Light *>& pointLightList,
        _IN_     const std::vector<const Light *>& spotLightList) const;

    virtual std::shared_ptr<VertexFormat>
    GetVertexFormat() const override;
};

}
