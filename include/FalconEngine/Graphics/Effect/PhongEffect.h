#pragma once

#include <FalconEngine/Core/Macro.h>

#include <memory>
#include <vector>

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

FALCON_ENGINE_CLASS_BEGIN PhongEffectParams :
public VisualEffectParams
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
    CreateInstance(_IN_OUT_ Node                                     *node,
                   _IN_     const std::shared_ptr<PhongEffectParams>& params);

protected:
    virtual std::shared_ptr<VertexFormat>
    CreateVertexFormat() const override;

    virtual std::shared_ptr<VertexFormat>
    GetVertexFormatSp() const override;

    // @summary Add required parameters to the existing visual effect instance.
    void
    InitializeInstance(_IN_OUT_ VisualEffectInstance                     *instance,
                       _IN_     const std::shared_ptr<Material>&          material,
                       _IN_     const std::shared_ptr<PhongEffectParams>& params) const;
};
FALCON_ENGINE_CLASS_END

}
