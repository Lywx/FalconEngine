#pragma once

#include <FalconEngine/GraphicsInclude.h>
#include <FalconEngine/Graphics/Renderer/VisualEffect.h>

namespace FalconEngine
{

class Light;
class Material;

class PhongLightingEffect : public VisualEffect
{
public:
    FALCON_ENGINE_RTTI_DECLARE;

    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    PhongLightingEffect();
    virtual ~PhongLightingEffect();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    // @summary Add required parameters to the existing visual effect instance.
    void
    CreateInstance(VisualEffectInstance *instance, const Light *light, const Material *material) const;
};

}
