#pragma once

#include <FalconEngine/Graphics/GraphicsInclude.h>
#include <FalconEngine/Graphics/Renderers/VisualPass.h>
#include <FalconEngine/Graphics/Renderers/States/BlendState.h>
#include <FalconEngine/Graphics/Renderers/States/CullState.h>
#include <FalconEngine/Graphics/Renderers/States/DepthTestState.h>
#include <FalconEngine/Graphics/Renderers/States/OffsetState.h>
#include <FalconEngine/Graphics/Renderers/States/StencilTestState.h>
#include <FalconEngine/Graphics/Renderers/States/WireframeState.h>
#include <FalconEngine/Graphics/Renderers/Shaders/Shader.h>
#include <FalconEngine/Graphics/Renderers/Shaders/ShaderUniformAutomatic.h>
#include <FalconEngine/Graphics/Renderers/Shaders/ShaderUniformConstant.h>
#include <FalconEngine/Graphics/Renderers/Shaders/ShaderUniformManual.h>

namespace FalconEngine
{

class VisualEffectInstance;
class VisualEffect;
using VisualEffectSharedPtr = std::shared_ptr<VisualEffect>;
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

    VisualEffectSharedPtr
    GetSharedPtr();

protected:
    void
    CheckEffectCompatible(VisualEffectInstance *instance) const;

protected:
    VisualEffectSharedPtr  mEffect;                                             // Effect shared_ptr controls the destruction of this class.
    VisualPassUniquePtrVector mPassHandleVector;                                   // Passes contained in this effect.
};

}
