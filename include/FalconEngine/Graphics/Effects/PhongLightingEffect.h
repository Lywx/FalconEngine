#pragma once

#include <FalconEngine/Graphics/GraphicsInclude.h>

#include <FalconEngine/Graphics/Renderers/VisualEffect.h>
#include <FalconEngine/Graphics/Renderers/VisualEffectInstance.h>
#include <FalconEngine/Graphics/Scenes/Light.h>
#include <FalconEngine/Graphics/Scenes/Material.h>

namespace FalconEngine
{

class PhongLightingEffect : public VisualEffect
{
public:
    FALCON_ENGINE_RTTI_DECLARE;

    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    PhongLightingEffect();
    virtual ~PhongLightingEffect();

    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    // @summary Add required parameters to the existing visual effect instance.
    void
    CreateInstance(VisualEffectInstance *instance, const Light *light, const Material *material) const;

    // @summary Create a new visual effect instance.
    VisualEffectInstanceSharedPtr
    CreateInstance(const Light *light, const Material *material);
};

}
