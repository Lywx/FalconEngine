#include <FalconEngine/Graphics/Renderers/VisualEffect.h>
#include <FalconEngine/Graphics/Renderers/VisualEffectInstance.h>
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

FALCON_ENGINE_RTTI_IMPLEMENT(VisualEffect, Object);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
VisualEffect::VisualEffect()
{
}

VisualEffect::~VisualEffect()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
VisualEffect::InsertPass(VisualPassUniquePtr pass)
{
    mPassHandleVector.push_back(move(pass));
}

VisualPass *
VisualEffect::GetPass(int passIndex)
{
    return mPassHandleVector.at(passIndex).get();
}

int
VisualEffect::GetPassNum() const
{
    return int(mPassHandleVector.size());
}

Shader *
VisualEffect::GetShader(int passIndex)
{
    return mPassHandleVector.at(passIndex)->GetShader();
}

const BlendState *
VisualEffect::GetBlendState(int passIndex) const
{
    return mPassHandleVector.at(passIndex)->GetBlendState();
}

const CullState *
VisualEffect::GetCullState(int passIndex) const
{
    return mPassHandleVector.at(passIndex)->GetCullState();
}

const DepthTestState *
VisualEffect::GetDepthTestState(int passIndex) const
{
    return mPassHandleVector.at(passIndex)->GetDepthTestState();
}

const OffsetState *
VisualEffect::GetOffsetState(int passIndex) const
{
    return mPassHandleVector.at(passIndex)->GetOffsetState();
}

const StencilTestState *
VisualEffect::GetStencilTestState(int passIndex) const
{
    return mPassHandleVector.at(passIndex)->GetStencilTestState();
}

const WireframeState *
VisualEffect::GetWireframeState(int passIndex) const
{
    return mPassHandleVector.at(passIndex)->GetWireframeState();
}

void
VisualEffect::CheckEffectCompatible(VisualEffectInstance *instance) const
{
    if (!GetType().IsExactly(instance->GetEffect()->GetType()))
    {
        FALCON_ENGINE_NOT_SUPPORT();
    }
}

}
