#pragma once

#include <FalconEngine/Core/Macro.h>

#include <functional>
#include <queue>

#include <FalconEngine/Graphics/Renderer/VisualEffect.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectParams.h>
#include <FalconEngine/Math/Color.h>

namespace FalconEngine
{

namespace Detail
{

FALCON_ENGINE_STRUCT_BEGIN PaintBufferData
{
    Matrix4f mModelViewProjectionTransform;
    Vector4f mColor;
};
FALCON_ENGINE_STRUCT_END

}

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
    FALCON_ENGINE_EFFECT_DECLARE(PaintEffect);

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    PaintEffect();
    virtual ~PaintEffect();

public:
    void
    CreateInstance(
        _IN_OUT_ Node                                     *node,
        _IN_     const std::shared_ptr<PaintEffectParams>& params);

protected:
    /************************************************************************/
    /* Protected Members                                                    */
    /************************************************************************/
    void
    InitializeInstance(
        _IN_OUT_ VisualEffectInstance                     *instance,
        _IN_     const std::shared_ptr<PaintEffectParams>& params) const;
};

}
