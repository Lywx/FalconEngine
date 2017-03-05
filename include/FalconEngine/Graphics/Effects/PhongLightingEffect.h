#pragma once

#include <FalconEngine/GraphicsInclude.h>
#include <FalconEngine/Graphics/Renderer/Scene/MeshEffect.h>

namespace FalconEngine
{

class Light;
class Material;
class Mesh;
class Node;

class Visual;
using VisualEffectSharedPtr = std::shared_ptr<VisualEffect>;
using VisualEffectInstanceSharedPtr = std::shared_ptr<VisualEffectInstance>;

class PhongLightingEffect : public MeshEffect
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
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
    CreateInstance(
        _IN_OUT_ VisualEffectInstance *instance,
        _IN_     const Light          *light,
        _IN_     const Material       *material) const;

    void
    CreateInstance(
        _IN_     VisualEffectSharedPtr effect,
        _IN_OUT_ Node                 *meshRoot,
        _IN_     const Light          *light);


private:
    void
    CreateInstance(
        _IN_OUT_ Mesh                         *mesh,
        _IN_OUT_ VisualEffectInstanceSharedPtr instance,
        _IN_     const Light                  *light) const;
};

}
