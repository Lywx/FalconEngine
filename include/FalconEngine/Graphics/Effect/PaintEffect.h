#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <functional>
#include <queue>

#include <FalconEngine/Graphics/Renderer/VisualEffect.h>
#include <FalconEngine/Math/Color.h>

namespace FalconEngine
{

class Visual;
class Mesh;
class Node;

#pragma warning(disable: 4251)
class FALCON_ENGINE_API PaintEffect : public VisualEffect
{
public:
    FALCON_ENGINE_EFFECT_DECLARE(PaintEffect);

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    PaintEffect();
    virtual ~PaintEffect();

public:
    void
    CreateInstance(_IN_OUT_ Node *node,
                   _IN_     Color color) const;

protected:
    virtual std::shared_ptr<VisualEffectInstance>
    CreateSetInstance(Visual *visual) const override;

    std::shared_ptr<VertexFormat>
    GetVertexFormat() const override;

    void
    InitializeInstance(_IN_OUT_ VisualEffectInstance *visualEffectInstance,
                       _IN_     Color                 color) const;
};
#pragma warning(default: 4251)

}
