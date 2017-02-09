#pragma once

#include <FalconEngine/Graphics/GraphicsInclude.h>
#include <FalconEngine/Graphics/Renderers/VisualPass.h>
#include <FalconEngine/Graphics/Renderers/States/BlendState.h>
#include <FalconEngine/Graphics/Renderers/States/CullState.h>
#include <FalconEngine/Graphics/Renderers/States/DepthTestState.h>
#include <FalconEngine/Graphics/Renderers/States/OffsetState.h>
#include <FalconEngine/Graphics/Renderers/States/StencilTestState.h>
#include <FalconEngine/Graphics/Renderers/States/WireframeState.h>
#include <FalconEngine/Graphics/Shaders/Shader.h>
#include <FalconEngine/Graphics/Shaders/ShaderUniformAutomatic.h>
#include <FalconEngine/Graphics/Shaders/ShaderUniformConstant.h>
#include <FalconEngine/Graphics/Shaders/ShaderUniformManual.h>

namespace FalconEngine
{

class VisualEffect;
using VisualEffectSharedPtr = std::shared_ptr<const VisualEffect>;
class VisualEffect : public Object
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    VisualEffect();
    virtual ~VisualEffect();

    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    InsertPass(VisualPassHandle pass);

    int
    GetPassNum() const;

    VisualPass *
    GetPass(int passIndex) const;

    Shader *
    GetShader(int passIndex) const;

    BlendState *
    GetBlendState(int passIndex) const;

    CullState *
    GetCullState(int passIndex) const;

    DepthTestState *
    GetDepthTestState(int passIndex) const;

    OffsetState *
    GetOffsetState(int passIndex) const;

    StencilTestState *
    GetStencilTestState(int passIndex) const;

    WireframeState *
    GetWireframeState(int passIndex) const;

    VisualEffectSharedPtr
    GetSharedPtr();

protected:
    VisualPassHandleVector mPassHandleVector;
    VisualEffectSharedPtr mThis;
};

}
