#include <FalconEngine/Graphics/Renderer/VisualEffectInstancePass.h>

#include <FalconEngine/Core/Exception.h>
#include <FalconEngine/Graphics/Renderer/Resource/Sampler.h>
#include <FalconEngine/Graphics/Renderer/Resource/SamplerBinding.h>
#include <FalconEngine/Graphics/Renderer/Resource/Shader.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture.h>
#include <FalconEngine/Graphics/Renderer/Resource/TextureBinding.h>
#include <FalconEngine/Graphics/Renderer/Resource/Uniform.h>
#include <FalconEngine/Graphics/Renderer/Resource/UniformBufferBinding.h>

using namespace std;

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
VisualEffectInstancePass::VisualEffectInstancePass(Shader *shader) :
    mInstancingNum(1),
    mShader(shader),
    mTextureUnitCount(0),
    mUniformBufferBindingIndexCount(0)
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
    return int(mSamplerBindingTable.size());
}

const Sampler *
VisualEffectInstancePass::GetSampler(int textureUnit)
{
    return mSamplerBindingTable.at(textureUnit).mSampler;
}

void
VisualEffectInstancePass::SetSampler(int textureUnit,
                                     const Sampler *sampler,
                                     unsigned int samplerShaderMask)
{
    FALCON_ENGINE_CHECK_NULLPTR(sampler);

    mSamplerBindingTable[textureUnit] = SamplerBinding(sampler, samplerShaderMask);
}


Shader *
VisualEffectInstancePass::GetShader() const
{
    return mShader;
}

int
VisualEffectInstancePass::GetTextureNum() const
{
    return int(mTextureBindingTable.size());
}

const Texture *
VisualEffectInstancePass::GetTexture(int textureUnit) const
{
    return mTextureBindingTable.at(textureUnit).mTexture;
}

void
VisualEffectInstancePass::SetTexture(
    int textureUnit,
    const Texture *texture,
    TextureMode textureMode,
    unsigned int textureShaderMask)
{
    FALCON_ENGINE_CHECK_NULLPTR(texture);

    if (mTextureBindingTable.find(textureUnit) != mTextureBindingTable.end())
    {
        mTextureBindingTable.at(textureUnit).mTextureShaderMaskList[int(textureMode)] = textureShaderMask;
    }
    else
    {
        mTextureBindingTable[textureUnit] = TextureBinding(texture, textureMode, textureShaderMask);
    }
}

Uniform *
VisualEffectInstancePass::GetUniform(int uniformIndex)
{
    return mUniformList.at(uniformIndex).get();
}

void
VisualEffectInstancePass::PushUniform(std::shared_ptr<Uniform> uniform)
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

void
VisualEffectInstancePass::PushUniformBuffer(std::shared_ptr<UniformBuffer> uniformBuffer, unsigned int shaderMask)
{
    FALCON_ENGINE_CHECK_NULLPTR(uniformBuffer);

    if (!mShader->ContainUniformBufferMeta(uniformBuffer->mName))
    {
        mShader->SetUniformBufferMeta(uniformBuffer->mName,
                                      uniformBuffer->GetCapacitySize(),
                                      mUniformBufferBindingIndexCount);
    }

    auto uniformBufferBinding = make_shared<UniformBufferBinding>(std::move(uniformBuffer), shaderMask);
    mUniformBufferBindingList.push_back(std::move(uniformBufferBinding));
    mUniformBufferBindingIndexCount += 1;
}

}
