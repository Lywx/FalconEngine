#include <FalconEngine/Graphics/Renderer/VisualEffectPass.h>

#include <FalconEngine/Core/Exception.h>
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
VisualEffectPass::SetShader(std::shared_ptr<Shader> shader)
{
    FALCON_ENGINE_CHECK_NULLPTR(shader);

    mShader = shader;
}

void
VisualEffectPass::SetBlendState(std::unique_ptr<BlendState> blendStateHandle)
{
    if (blendStateHandle == nullptr)
    {
        FALCON_ENGINE_THROW_NULLPTR_EXCEPTION(blendStateHandle);
    }

    mBlendState.reset(blendStateHandle.release());
}

void
VisualEffectPass::SetCullState(std::unique_ptr<CullState> cullStateHandle)
{
    if (cullStateHandle == nullptr)
    {
        FALCON_ENGINE_THROW_NULLPTR_EXCEPTION(blendStateHandle);
    }

    mCullState.reset(cullStateHandle.release());
}

void
VisualEffectPass::SetDepthTestState(std::unique_ptr<DepthTestState> depthTestStateHandle)
{
    if (depthTestStateHandle == nullptr)
    {
        FALCON_ENGINE_THROW_NULLPTR_EXCEPTION(blendStateHandle);
    }

    mDepthTestState.reset(depthTestStateHandle.release());
}

void
VisualEffectPass::SetOffsetState(std::unique_ptr<OffsetState> offsetStateHandle)
{
    if (offsetStateHandle == nullptr)
    {
        FALCON_ENGINE_THROW_NULLPTR_EXCEPTION(blendStateHandle);
    }

    mOffsetState.reset(offsetStateHandle.release());
}

void
VisualEffectPass::SetStencilTestState(std::unique_ptr<StencilTestState> stencilTestStateHandle)
{
    if (stencilTestStateHandle == nullptr)
    {
        FALCON_ENGINE_THROW_NULLPTR_EXCEPTION(blendStateHandle);
    }

    mStencilTestState.reset(stencilTestStateHandle.release());
}

void
VisualEffectPass::SetWireframeState(std::unique_ptr<WireframeState> wireframeStateHandle)
{
    if (wireframeStateHandle == nullptr)
    {
        FALCON_ENGINE_THROW_NULLPTR_EXCEPTION(blendStateHandle);
    }

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

BlendState *
VisualEffectPass::GetBlendState()
{
    return mBlendState.get();
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

CullState *
VisualEffectPass::GetCullState()
{
    return mCullState.get();
}

const DepthTestState *
VisualEffectPass::GetDepthTestState() const
{
    return mDepthTestState.get();
}

DepthTestState *
VisualEffectPass::GetDepthTestState()
{
    return mDepthTestState.get();
}

const OffsetState *
VisualEffectPass::GetOffsetState() const
{
    return mOffsetState.get();
}

OffsetState *
VisualEffectPass::GetOffsetState()
{
    return mOffsetState.get();
}

const StencilTestState *
VisualEffectPass::GetStencilTestState() const
{
    return mStencilTestState.get();
}

StencilTestState *
VisualEffectPass::GetStencilTestState()
{
    return mStencilTestState.get();
}

const WireframeState *
VisualEffectPass::GetWireframeState() const
{
    return mWireframeState.get();
}

WireframeState *
VisualEffectPass::GetWireframeState()
{
    return mWireframeState.get();
}
}
