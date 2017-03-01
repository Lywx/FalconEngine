#pragma once

#include <FalconEngine/GraphicsInclude.h>

#include <vector>

#include <FalconEngine/Core/Object.h>

namespace FalconEngine
{

class VisualEffectInstance;

class VisualPass;
using VisualPassUniquePtr = std::unique_ptr<VisualPass>;

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
    InsertPass(VisualPassUniquePtr pass);

    int
    GetPassNum() const;

    VisualPass *
    GetPass(int passIndex);

    Shader *
    GetShader(int passIndex);
    ;
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

protected:
    std::vector<VisualPassUniquePtr> mPassHandleVector; // Passes contained in this effect.
};

}
