#include <FalconEngine/Graphics/Renderer/VisualEffectPass.h>
#include <FalconEngine/Graphics/Renderer/State/BlendState.h>
#include <FalconEngine/Graphics/Renderer/State/CullState.h>
#include <FalconEngine/Graphics/Renderer/State/DepthTestState.h>
#include <FalconEngine/Graphics/Renderer/State/OffsetState.h>
#include <FalconEngine/Graphics/Renderer/State/StencilTestState.h>
#include <FalconEngine/Graphics/Renderer/State/WireframeState.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture.h>
#include <FalconEngine/Graphics/Renderer/Resource/Sampler.h>
#include <FalconEngine/Graphics/Renderer/Shader/Shader.h>
#include <FalconEngine/Graphics/Renderer/Shader/ShaderUniform.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
VisualEffectPass::VisualEffectPass()
{
}

VisualEffectPass::~VisualEffectPass()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
VisualEffectPass::SetShader(ShaderSharedPtr shader)
{
    mShader = shader;
}

void
VisualEffectPass::SetBlendState(BlendStateUniquePtr blendStateHandle)
{
    mBlendState.reset(blendStateHandle.release());
}

void
VisualEffectPass::SetCullState(CullStateUniquePtr cullStateHandle)
{
    mCullState.reset(cullStateHandle.release());
}

void
VisualEffectPass::SetDepthTestState(DepthTestStateUniquePtr depthTestStateHandle)
{
    mDepthTestState.reset(depthTestStateHandle.release());
}

void
VisualEffectPass::SetOffsetState(OffsetStateUniquePtr offsetStateHandle)
{
    mOffsetState.reset(offsetStateHandle.release());
}

void
VisualEffectPass::SetStencilTestState(StencilTestStateUniquePtr stencilTestStateHandle)
{
    mStencilTestState.reset(stencilTestStateHandle.release());
}

void
VisualEffectPass::SetWireframeState(WireframeStateUniquePtr wireframeStateHandle)
{
    mWireframeState.reset(wireframeStateHandle.release());
}

const Shader *
VisualEffectPass::GetShader() const
{
    return mShader.get();
}

Shader *
VisualEffectPass::GetShader()
{
    return mShader.get();
}

const BlendState *
VisualEffectPass::GetBlendState() const
{
    return mBlendState.get();
}

const CullState *
VisualEffectPass::GetCullState() const
{
    return mCullState.get();
}

const DepthTestState *
VisualEffectPass::GetDepthTestState() const
{
    return mDepthTestState.get();
}

const OffsetState *
VisualEffectPass::GetOffsetState() const
{
    return mOffsetState.get();
}

const StencilTestState *
VisualEffectPass::GetStencilTestState() const
{
    return mStencilTestState.get();
}

const WireframeState *
VisualEffectPass::GetWireframeState() const
{
    return mWireframeState.get();
}

}
