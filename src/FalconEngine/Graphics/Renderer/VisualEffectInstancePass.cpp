#include <FalconEngine/Graphics/Renderer/VisualEffectInstancePass.h>

#include <FalconEngine/Core/Exception.h>
#include <FalconEngine/Graphics/Renderer/Shader/Shader.h>
#include <FalconEngine/Graphics/Renderer/Shader/ShaderUniform.h>
#include <FalconEngine/Graphics/Renderer/Resource/Sampler.h>
#include <FalconEngine/Graphics/Renderer/Resource/SamplerAttachment.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture.h>
#include <FalconEngine/Graphics/Renderer/Resource/TextureAttachment.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
VisualEffectInstancePass::VisualEffectInstancePass(Shader *shader) :
    mShader(shader),
    mShaderInstancingNum(1)
{
}

VisualEffectInstancePass::~VisualEffectInstancePass()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
VisualEffectInstancePass::SetShaderUniform(std::shared_ptr<ShaderUniform> shaderUniform)
{
    FALCON_ENGINE_CHECK_NULLPTR(shaderUniform);

    if (!mShader->ContainUniform(shaderUniform->mName))
    {
        mShader->PushUniform(shaderUniform->mName, shaderUniform->mType);
    }

    mShaderUniformList.push_back(shaderUniform);
}

void
VisualEffectInstancePass::SetShaderTexture(
    int textureUnit,
    const Texture *texture,
    TextureMode textureMode,
    unsigned int textureShaderMask)
{
    FALCON_ENGINE_CHECK_NULLPTR(texture);

    if (mShaderTextureTable.find(textureUnit) != mShaderTextureTable.end())
    {
        mShaderTextureTable.at(textureUnit).mTextureShaderMaskList[int(textureMode)] = textureShaderMask;
    }
    else
    {
        mShaderTextureTable[textureUnit] = TextureAttachment(texture, textureMode, textureShaderMask);
    }
}

void
VisualEffectInstancePass::SetShaderSampler(int textureUnit,
        const Sampler *sampler,
        unsigned int samplerShaderMask)
{
    FALCON_ENGINE_CHECK_NULLPTR(sampler);

    mShaderSamplerTable[textureUnit] = SamplerAttachment(sampler, samplerShaderMask);
}

Shader *
VisualEffectInstancePass::GetShader() const
{
    return mShader;
}

int
VisualEffectInstancePass::GetShaderInstancingNum() const
{
    return mShaderInstancingNum;
}

void
VisualEffectInstancePass::SetShaderInstancingNum(int instancingNum)
{
    mShaderInstancingNum = instancingNum;
}

int
VisualEffectInstancePass::GetShaderUniformNum() const
{
    return int(mShaderUniformList.size());
}

ShaderUniform *
VisualEffectInstancePass::GetShaderUniform(int uniformIndex) const
{
    return mShaderUniformList.at(uniformIndex).get();
}

int
VisualEffectInstancePass::GetShaderTextureNum() const
{
    return int(mShaderTextureTable.size());
}

const Texture *
VisualEffectInstancePass::GetShaderTexture(int textureUnit) const
{
    return mShaderTextureTable.at(textureUnit).mTexture;
}

int
VisualEffectInstancePass::GetShaderSamplerNum() const
{
    return int(mShaderSamplerTable.size());
}

const Sampler *
VisualEffectInstancePass::GetShaderSampler(int textureUnit)
{
    return mShaderSamplerTable.at(textureUnit).mSampler;
}
}
