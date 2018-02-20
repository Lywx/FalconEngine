#include <FalconEngine/Graphics/Renderer/VisualEffectInstancePass.h>

#include <FalconEngine/Core/Exception.h>
#include <FalconEngine/Graphics/Renderer/Resource/Shader.h>
#include <FalconEngine/Graphics/Renderer/Resource/Uniform.h>
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
    mInstancingNum(1)
{
}

VisualEffectInstancePass::~VisualEffectInstancePass()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
int
VisualEffectInstancePass::GetInstancingNum() const
{
    return mInstancingNum;
}

void
VisualEffectInstancePass::SetInstancingNum(int instancingNum)
{
    mInstancingNum = instancingNum;
}

int
VisualEffectInstancePass::GetSamplerNum() const
{
    return int(mSamplerTable.size());
}

const Sampler *
VisualEffectInstancePass::GetSampler(int textureUnit)
{
    return mSamplerTable.at(textureUnit).mSampler;
}

void
VisualEffectInstancePass::SetSampler(int textureUnit,
                                     const Sampler *sampler,
                                     unsigned int samplerShaderMask)
{
    FALCON_ENGINE_CHECK_NULLPTR(sampler);

    mSamplerTable[textureUnit] = SamplerAttachment(sampler, samplerShaderMask);
}


Shader *
VisualEffectInstancePass::GetShader() const
{
    return mShader;
}

int
VisualEffectInstancePass::GetTextureNum() const
{
    return int(mTextureTable.size());
}

const Texture *
VisualEffectInstancePass::GetTexture(int textureUnit) const
{
    return mTextureTable.at(textureUnit).mTexture;
}

void
VisualEffectInstancePass::SetTexture(
    int textureUnit,
    const Texture *texture,
    TextureMode textureMode,
    unsigned int textureShaderMask)
{
    FALCON_ENGINE_CHECK_NULLPTR(texture);

    if (mTextureTable.find(textureUnit) != mTextureTable.end())
    {
        mTextureTable.at(textureUnit).mTextureShaderMaskList[int(textureMode)] = textureShaderMask;
    }
    else
    {
        mTextureTable[textureUnit] = TextureAttachment(texture, textureMode, textureShaderMask);
    }
}

Uniform *
VisualEffectInstancePass::GetUniform(int uniformIndex)
{
    return mUniformList.at(uniformIndex).get();
}

void
VisualEffectInstancePass::SetUniform(std::shared_ptr<Uniform> uniform)
{
    FALCON_ENGINE_CHECK_NULLPTR(uniform);

    if (!mShader->ContainUniformMeta(uniform->mName))
    {
        mShader->SetUniformMeta(uniform->mName);
    }

    mUniformList.push_back(std::move(uniform));
}

int
VisualEffectInstancePass::GetUniformNum() const
{
    return int(mUniformList.size());
}

UniformBuffer *
VisualEffectInstancePass::GetUniformBuffer(int uniformBufferIndex)
{
    return mUniformBufferList.at(uniformBufferIndex).get();
}

void
VisualEffectInstancePass::SetUniformBuffer(std::shared_ptr<UniformBuffer> uniformBuffer)
{
    FALCON_ENGINE_CHECK_NULLPTR(uniformBuffer);

    if (!mShader->ContainUniformBufferMeta(uniformBuffer->GetName()))
    {
        mShader->SetUniformBufferMeta(uniformBuffer->GetName(), uniformBuffer->GetCapacitySize());
    }

    mUniformBufferList.push_back(std::move(uniformBuffer));
}

int
VisualEffectInstancePass::GetUniformBufferNum() const
{
    return int(mUniformBufferList.size());
}

}
