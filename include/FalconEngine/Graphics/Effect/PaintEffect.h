#pragma once

#include <FalconEngine/Graphics/Common.h>

#include <functional>
#include <queue>

#include <FalconEngine/Graphics/Renderer/VisualEffect.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectParams.h>
#include <FalconEngine/Math/Color.h>

namespace FalconEngine
{

class Visual;
class Mesh;
class Node;

class FALCON_ENGINE_API PaintEffectParams : public VisualEffectParams
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    PaintEffectParams(Color color) :
        mColor(color)
    {
    }

public:
    Color mColor;
};

class FALCON_ENGINE_API PaintEffect : public VisualEffect
{
public:
    FALCON_ENGINE_EFFECT_GLOBAL_DECLARE(PaintEffect);

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    PaintEffect();
    virtual ~PaintEffect();

public:
    void
    CreateInstance(
        _IN_OUT_ Node                              *node,
        _IN_     std::shared_ptr<PaintEffectParams> params) const;

protected:
    virtual std::shared_ptr<VertexFormat>
    CreateVertexFormat() const override;

    virtual std::shared_ptr<VertexFormat>
    GetVertexFormat() const override;

    void
    InitializeInstance(
        _IN_OUT_ VisualEffectInstance              *instance,
        _IN_     std::shared_ptr<PaintEffectParams> params) const;
};

}
