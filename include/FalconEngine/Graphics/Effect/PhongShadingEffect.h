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

class PhongShadingEffect;

class FALCON_ENGINE_API PhongShadingEffect : public VisualEffect
{
    FALCON_ENGINE_RTTI_DECLARE;

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
    void
    CreateInstance(
        _IN_ std::shared_ptr<VisualEffect>         visualEffect,
        _IN_OUT_ Node                             *node,
        _IN_     const Light&                      directionalLight,
        _IN_     const std::vector<const Light *>& pointLightList,
        _IN_     const std::vector<const Light *>& spotLightList);

    // @summary Add required parameters to the existing visual effect instance.
    void
    CreateInstance(
        _IN_OUT_ VisualEffectInstance         *visualEffectInstance,
        _IN_ const Material&                   material,
        _IN_ const Light&                      directionalLight,
        _IN_ const std::vector<const Light *>& pointLightList,
        _IN_ const std::vector<const Light *>& spotLightList) const;

    virtual std::shared_ptr<VertexFormat>
    GetVertexFormat() const override;

private:
    void
    CreateInstance(
        _IN_OUT_ std::shared_ptr<VisualEffectInstance> visualEffectInstance,
        _IN_OUT_ Visual                               *visual,
        _IN_     const Light&                          directionalLight,
        _IN_     const std::vector<const Light *>&     pointLightList,
        _IN_     const std::vector<const Light *>&     spotLightList) const;
};

}
