#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <functional>
#include <memory>

#include <FalconEngine/Graphics/Renderer/VisualEffect.h>
#include <FalconEngine/Math/Color.h>

namespace FalconEngine
{

class Visual;
class Mesh;
class Node;

// @summary Implements material coloring with mesh visualization.
#pragma warning(disable: 4251)
class FALCON_ENGINE_API MeshEffect : public VisualEffect
{
    FALCON_ENGINE_EFFECT_DECLARE(MeshEffect);

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    MeshEffect();
    virtual ~MeshEffect();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    CreateInstance(_IN_ Node  *node,
                   _IN_ Color& ambient,
                   _IN_ Color& lineColor,
                   _IN_ float& lineWidth,
                   _IN_ bool&  texturing) const;

protected:
    /************************************************************************/
    /* Protected Members                                                    */
    /************************************************************************/
    virtual std::shared_ptr<VisualEffectInstance>
    CreateSetInstance(Visual *visual) const override;

    std::shared_ptr<VertexFormat>
    GetVertexFormat() const override;

    void
    InitializeInstance(_IN_OUT_ VisualEffectInstance *visualEffectInstance,
                       _IN_     Color&                ambient,
                       _IN_     const Material&       material,
                       _IN_     Color&                color,
                       _IN_     float&                width,
                       _IN_     bool&                 texturing) const;
};
#pragma warning(default: 4251)

}
