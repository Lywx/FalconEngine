#include <FalconEngine/Graphics/Renderer/VisualEffect.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectInstance.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectPass.h>
#include <FalconEngine/Graphics/Renderer/Scene/Visual.h>
#include <FalconEngine/Graphics/Renderer/State/BlendState.h>
#include <FalconEngine/Graphics/Renderer/State/CullState.h>
#include <FalconEngine/Graphics/Renderer/State/DepthTestState.h>
#include <FalconEngine/Graphics/Renderer/State/OffsetState.h>
#include <FalconEngine/Graphics/Renderer/State/StencilTestState.h>
#include <FalconEngine/Graphics/Renderer/State/WireframeState.h>
#include <FalconEngine/Graphics/Renderer/Shader/Shader.h>
#include <FalconEngine/Graphics/Renderer/Shader/ShaderUniformAutomatic.h>
#include <FalconEngine/Graphics/Renderer/Shader/ShaderUniformConstant.h>
#include <FalconEngine/Graphics/Renderer/Shader/ShaderUniformManual.h>

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
VisualEffect::InsertPass(VisualEffectPassUniquePtr pass)
{
    mPassList.push_back(move(pass));
}

const VisualEffectPass *
VisualEffect::GetPass(int passIndex) const
{
    return mPassList.at(passIndex).get();
}

VisualEffectPass *
VisualEffect::GetPass(int passIndex)
{
    return mPassList.at(passIndex).get();
}

int
VisualEffect::GetPassNum() const
{
    return int(mPassList.size());
}

Shader *
VisualEffect::GetShader(int passIndex)
{
    return mPassList.at(passIndex)->GetShader();
}

const BlendState *
VisualEffect::GetBlendState(int passIndex) const
{
    return mPassList.at(passIndex)->GetBlendState();
}

const CullState *
VisualEffect::GetCullState(int passIndex) const
{
    return mPassList.at(passIndex)->GetCullState();
}

const DepthTestState *
VisualEffect::GetDepthTestState(int passIndex) const
{
    return mPassList.at(passIndex)->GetDepthTestState();
}

const OffsetState *
VisualEffect::GetOffsetState(int passIndex) const
{
    return mPassList.at(passIndex)->GetOffsetState();
}

const StencilTestState *
VisualEffect::GetStencilTestState(int passIndex) const
{
    return mPassList.at(passIndex)->GetStencilTestState();
}

const WireframeState *
VisualEffect::GetWireframeState(int passIndex) const
{
    return mPassList.at(passIndex)->GetWireframeState();
}

void
VisualEffect::CheckEffectCompatible(VisualEffectInstance *instance) const
{
    if (!GetType().IsExactly(instance->GetEffect()->GetType()))
    {
        FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
    }
}

void
VisualEffect::CheckEffectSame(VisualEffect *effect) const
{
    if (this != effect)
    {
        FALCON_ENGINE_THROW_EXCEPTION("Effect is supposed to be the same.");
    }
}

void
VisualEffect::SetEffectInstance(Visual *visual, VisualEffectInstanceSharedPtr instance) const
{
    visual->SetEffectInstance(instance);
}

}
