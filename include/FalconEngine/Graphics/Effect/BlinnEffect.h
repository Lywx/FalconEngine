#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <FalconEngine/Graphics/Effect/PhongEffect.h>

namespace FalconEngine
{

class FALCON_ENGINE_API BlinnEffectParams : public PhongEffectParams
{
public:
    using PhongEffectParams::PhongEffectParams;
};

#pragma warning(disable: 4251)
class FALCON_ENGINE_API BlinnEffect : public PhongEffect
{
    FALCON_ENGINE_EFFECT_DECLARE(BlinnEffect);

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit BlinnEffect(bool initializer = true);
    virtual ~BlinnEffect();
};
#pragma warning(default: 4251)

}

