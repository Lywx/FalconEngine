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
/* Shader Management                                                    */
/************************************************************************/
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

void
VisualEffectPass::SetShader(std::shared_ptr<Shader> shader)
{
    FALCON_ENGINE_CHECK_NULLPTR(shader);

    mShader = std::move(shader);
}

const VertexFormat *
VisualEffectPass::GetShaderVertexFormat() const
{
    return mShaderVertexFormat.get();
}

VertexFormat *
VisualEffectPass::GetShaderVertexFormat()
{
    return mShaderVertexFormat.get();
}

std::shared_ptr<VertexFormat>
VisualEffectPass::GetShaderVertexFormatSp()
{
    return mShaderVertexFormat;
}

void
VisualEffectPass::SetShaderVertexFormat(std::shared_ptr<VertexFormat> shaderVertexFormat)
{
    FALCON_ENGINE_CHECK_NULLPTR(shaderVertexFormat);

    mShaderVertexFormat = std::move(shaderVertexFormat);
}

/************************************************************************/
/* State Management                                                     */
/************************************************************************/
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

void
VisualEffectPass::SetBlendState(std::unique_ptr<BlendState> blendStateHandle)
{
    FALCON_ENGINE_CHECK_NULLPTR(blendStateHandle);

    mBlendState.reset(blendStateHandle.release());
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

void
VisualEffectPass::SetCullState(std::unique_ptr<CullState> cullStateHandle)
{
    FALCON_ENGINE_CHECK_NULLPTR(cullStateHandle);

    mCullState.reset(cullStateHandle.release());
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

void
VisualEffectPass::SetDepthTestState(std::unique_ptr<DepthTestState> depthTestStateHandle)
{
    FALCON_ENGINE_CHECK_NULLPTR(depthTestStateHandle);

    mDepthTestState.reset(depthTestStateHandle.release());
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

void
VisualEffectPass::SetOffsetState(std::unique_ptr<OffsetState> offsetStateHandle)
{
    FALCON_ENGINE_CHECK_NULLPTR(offsetStateHandle);

    mOffsetState.reset(offsetStateHandle.release());
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

void
VisualEffectPass::SetStencilTestState(std::unique_ptr<StencilTestState> stencilTestStateHandle)
{
    FALCON_ENGINE_CHECK_NULLPTR(stencilTestStateHandle);

    mStencilTestState.reset(stencilTestStateHandle.release());
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

void
VisualEffectPass::SetWireframeState(std::unique_ptr<WireframeState> wireframeStateHandle)
{
    FALCON_ENGINE_CHECK_NULLPTR(wireframeStateHandle);

    mWireframeState.reset(wireframeStateHandle.release());
}

}
