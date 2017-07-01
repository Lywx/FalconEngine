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

#pragma pack(push, 1)
class FALCON_ENGINE_API DebugVertex
{
public:
    Vector2f mPosition;
    Vector4f mColor;
};
#pragma pack(pop)

class FALCON_ENGINE_API DebugEffectParams : public VisualEffectParams
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    DebugEffectParams()
    {
    }
};

class FALCON_ENGINE_API DebugEffect : public VisualEffect
{
public:
    FALCON_ENGINE_EFFECT_DECLARE(DebugEffect);

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    DebugEffect();
    virtual ~DebugEffect();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    CreateInstance(_IN_OUT_ Visual                            *visual,
                   _IN_     std::shared_ptr<DebugEffectParams> params) const;

    virtual std::shared_ptr<VertexFormat>
    GetVertexFormat() const override;

    /************************************************************************/
    /* Protected Members                                                    */
    /************************************************************************/
protected:
    virtual std::shared_ptr<VertexFormat>
    CreateVertexFormat() const override;

    void
    InitializeInstance(
        _IN_OUT_ VisualEffectInstance              *instance,
        _IN_     std::shared_ptr<DebugEffectParams> params) const;
};

}
