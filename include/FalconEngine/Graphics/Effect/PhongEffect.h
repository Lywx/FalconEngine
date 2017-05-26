#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <FalconEngine/Graphics/Renderer/VisualEffect.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectParams.h>

namespace FalconEngine
{

class Light;
class Material;
class Mesh;
class Node;

class Visual;
class VisualEffectInstance;

#pragma warning(disable: 4251)
class FALCON_ENGINE_API PhongEffectParams : public VisualEffectParams
{
public:
    PhongEffectParams() = default;

public:
    std::shared_ptr<Light>              mDirectionalLight;
    std::vector<std::shared_ptr<Light>> mPointLightList;
    std::vector<std::shared_ptr<Light>> mSpotLightList;
};

class FALCON_ENGINE_API PhongEffect : public VisualEffect
{
    FALCON_ENGINE_EFFECT_DECLARE(PhongEffect);

public:
    static int PointLightNumMax;
    static int SpotLightNumMax;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PhongEffect(bool initializer = true);
    virtual ~PhongEffect();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    CreateInstance(_IN_OUT_ Node                       *node,
                   _IN_     const PhongEffectParams   *params) const;

    // @summary Add required parameters to the existing visual effect instance.
    // @remark Need a shared_ptr of visual effect of its own because this method
    // need to create visual effect instance for all visual whose rooted to given
    // node. Creation of visual effect instance need this shared_ptr. But the
    // shared_ptr has to be used carefully for itself because it manage the
    // lifetime of the object. You won't want to store a shared_ptr of itself
    // because it would cause the destructor to call twice.
    void
    CreateInstance(_IN_OUT_ Node                                      *node,
                   _IN_     const std::shared_ptr<Light>               directionalLight,
                   _IN_     const std::vector<std::shared_ptr<Light>>& pointLightList,
                   _IN_     const std::vector<std::shared_ptr<Light>>& spotLightList) const;

protected:
    virtual std::shared_ptr<VisualEffectInstance>
    CreateSetInstance(Visual *visual) const override;

    // @summary Add required parameters to the existing visual effect instance.
    void
    InitializeInstance(
        _IN_OUT_ VisualEffectInstance                      *visualEffectInstance,
        _IN_     std::shared_ptr<Material>                  material,
        _IN_     std::shared_ptr<Light>                     directionalLight,
        _IN_     const std::vector<std::shared_ptr<Light>>& pointLightList,
        _IN_     const std::vector<std::shared_ptr<Light>>& /* spotLightList */) const;

    virtual std::shared_ptr<VertexFormat>
    GetVertexFormat() const override;
};
#pragma warning(default: 4251)

}
