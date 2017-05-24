#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <FalconEngine/Graphics/Effect/PhongShadingEffect.h>

namespace FalconEngine
{

#pragma warning(disable: 4251)
class FALCON_ENGINE_API BlinnPhongShadingEffect : public PhongShadingEffect
{
    FALCON_ENGINE_EFFECT_DECLARE(BlinnPhongShadingEffect);

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit BlinnPhongShadingEffect(bool initializer = true);
    virtual ~BlinnPhongShadingEffect();

protected:
    virtual std::shared_ptr<VisualEffectInstance>
    CreateSetInstance(Visual *visual) const override;
};
#pragma warning(default: 4251)

}

