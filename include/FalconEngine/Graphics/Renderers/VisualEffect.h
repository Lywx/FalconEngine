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
    InsertPass(VisualPassHandle pass);

    int
    GetPassNum() const;

    VisualPass *
    GetPass(int passIndex);

    Shader *
    GetShader(int passIndex);

    BlendState *
    GetBlendState(int passIndex);

    CullState *
    GetCullState(int passIndex);

    DepthTestState *
    GetDepthTestState(int passIndex);

    OffsetState *
    GetOffsetState(int passIndex);

    StencilTestState *
    GetStencilTestState(int passIndex);

    WireframeState *
    GetWireframeState(int passIndex);

    VisualEffectSharedPtr
    GetSharedPtr();

protected:
    VisualEffectSharedPtr  mEffect;                                             // Effect shared_ptr controls the destruction of this class.
    VisualPassHandleVector mPassHandleVector;                                   // Passes contained in this effect.
};

}
