#include <FalconEngine/Graphics/Renderers/VisualPass.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(VisualPass, Object);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
VisualPass::VisualPass()
{
}

VisualPass::~VisualPass()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
VisualPass::SetShader(ShaderSharedPtr shader)
{
    mShader = shader;
}

void
VisualPass::SetShaderUniform(ShaderUniform *shaderUniform)
{
    if (mShader->ContainUniform(shaderUniform->mName))
    {
        mShaderUniformVector.push_back(shaderUniform);
    }
    else
    {
        ThrowRuntimeException("Uniform is not registered");
    }
}

void
VisualPass::SetShaderTexture(int textureUnit, const Texture *texture)
{
    FALCON_ENGINE_CHECK_NULLPTR(texture);

    mShaderTextureTable[textureUnit] = texture;
}

void
VisualPass::SetShaderSampler(int textureUnit, const Sampler *sampler)
{
    FALCON_ENGINE_CHECK_NULLPTR(sampler);

    mShaderSamplerTable[textureUnit] = sampler;
}

void
VisualPass::SetBlendState(BlendStateUniquePtr blendStateHandle)
{
    mBlendStateHandle.reset(blendStateHandle.release());
}

void
VisualPass::SetCullState(CullStateUniquePtr cullStateHandle)
{
    mCullStateHandle.reset(cullStateHandle.release());
}

void
VisualPass::SetDepthTestState(DepthTestStateUniquePtr depthTestStateHandle)
{
    mDepthTestStateHandle.reset(depthTestStateHandle.release());
}

void
VisualPass::SetOffsetState(OffsetStateUniquePtr offsetStateHandle)
{
    mOffsetStateHandle.reset(offsetStateHandle.release());
}

void
VisualPass::SetStencilTestState(StencilTestStateUniquePtr stencilTestStateHandle)
{
    mStencilTestStateHandle.reset(stencilTestStateHandle.release());
}

void
VisualPass::SetWireframeState(WireframeStateUniquePtr wireframeStateHandle)
{
    mWireframeStateHandle.reset(wireframeStateHandle.release());
}

Shader *
VisualPass::GetShader() const
{
    return mShader.get();
}

int
VisualPass::GetShaderUniformNum() const
{
    return int(mShaderUniformVector.size());
}

ShaderUniform *
VisualPass::GetShaderUniform(int uniformIndex) const
{
    return mShaderUniformVector.at(uniformIndex);
}

int
VisualPass::GetShaderTextureNum() const
{
    return int(mShaderTextureTable.size());
}

const Texture *
VisualPass::GetShaderTexture(int textureUnit) const
{
    return mShaderTextureTable.at(textureUnit);
}

int
VisualPass::GetShaderSamplerNum() const
{
    return int(mShaderSamplerTable.size());
}

const Sampler *
VisualPass::GetShaderSampler(int textureUnit)
{
    return mShaderSamplerTable.at(textureUnit);
}

const BlendState *
VisualPass::GetBlendState() const
{
    return mBlendStateHandle.get();
}

const CullState *
VisualPass::GetCullState() const
{
    return mCullStateHandle.get();
}

const DepthTestState *
VisualPass::GetDepthTestState() const
{
    return mDepthTestStateHandle.get();
}

const OffsetState *
VisualPass::GetOffsetState() const
{
    return mOffsetStateHandle.get();
}

const StencilTestState *
VisualPass::GetStencilTestState() const
{
    return mStencilTestStateHandle.get();
}

const WireframeState *
VisualPass::GetWireframeState() const
{
    return mWireframeStateHandle.get();
}

}
