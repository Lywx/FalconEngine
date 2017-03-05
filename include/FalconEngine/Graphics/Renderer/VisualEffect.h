#pragma once

#include <FalconEngine/GraphicsInclude.h>

#include <vector>

#include <FalconEngine/Core/Object.h>

namespace FalconEngine
{

class Visual;
class VisualEffectInstance;
using VisualEffectInstanceSharedPtr = std::shared_ptr<VisualEffectInstance>;

class VisualEffectPass;
using VisualEffectPassUniquePtr = std::unique_ptr<VisualEffectPass>;

class Shader;
class BlendState;
class CullState;
class DepthTestState;
class OffsetState;
class StencilTestState;
class WireframeState;

class VisualEffect : public Object
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    VisualEffect();

    // @remark You should not manually call destructor of VisualEffect. The
    // destructor would be called by shared_ptr.
    virtual ~VisualEffect();

    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    InsertPass(VisualEffectPassUniquePtr pass);

    int
    GetPassNum() const;

    const VisualEffectPass *
    GetPass(int passIndex) const;

    VisualEffectPass *
    GetPass(int passIndex);

    Shader *
    GetShader(int passIndex);

    const BlendState *
    GetBlendState(int passIndex) const;

    const CullState *
    GetCullState(int passIndex) const;

    const DepthTestState *
    GetDepthTestState(int passIndex) const;

    const OffsetState *
    GetOffsetState(int passIndex) const;

    const StencilTestState *
    GetStencilTestState(int passIndex) const;

    const WireframeState *
    GetWireframeState(int passIndex) const;

protected:
    void
    CheckEffectCompatible(VisualEffectInstance *instance) const;

    void
    CheckEffectSame(VisualEffect *effect) const;

    void
    SetEffectInstance(
        _IN_OUT_ Visual                       *visual,
        _IN_     VisualEffectInstanceSharedPtr instance) const;

protected:
    std::vector<VisualEffectPassUniquePtr> mPassList; // Passes contained in this effect.
};

}
