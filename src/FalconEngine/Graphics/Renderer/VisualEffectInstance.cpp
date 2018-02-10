#include <FalconEngine/Graphics/Renderer/VisualEffectInstance.h>
#include <FalconEngine/Graphics/Renderer/VisualEffect.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectPass.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture.h>
#include <FalconEngine/Graphics/Renderer/Resource/Sampler.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
VisualEffectInstance::VisualEffectInstance(std::shared_ptr<VisualEffect> effect) :
    mEffect(effect)
{
    for (int i = 0; i < mEffect->GetPassNum(); ++i)
    {
        mEffectInstancePassList.push_back(std::make_unique<VisualEffectInstancePass>(mEffect->GetShader(i)));
    }
}

VisualEffectInstance::~VisualEffectInstance()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
const VisualEffect *
VisualEffectInstance::GetEffect() const
{
    return mEffect.get();
}

int
VisualEffectInstance::GetPassNum() const
{
    return mEffect->GetPassNum();
}

VisualEffectInstancePass *
VisualEffectInstance::GetPass(int passIndex)
{
    return mEffectInstancePassList.at(passIndex).get();
}

int
VisualEffectInstance::GetShaderInstancingNum(int passIndex) const
{
    return mEffectInstancePassList.at(passIndex)->GetShaderInstancingNum();
}

void
VisualEffectInstance::SetShaderInstancingNum(int passIndex, int instancingNum)
{
    mEffectInstancePassList.at(passIndex)->SetShaderInstancingNum(instancingNum);
}

const Texture *
VisualEffectInstance::GetShaderTexture(int passIndex, int textureUnit) const
{
    return mEffectInstancePassList.at(passIndex)->GetShaderTexture(textureUnit);
}

void
VisualEffectInstance::SetShaderTexture(int passIndex, int textureUnit, const Texture *texture,
                                       TextureMode textureMode, ShaderType shaderType)
{
    SetShaderTexture(passIndex, textureUnit, texture, textureMode, GetShaderMask(shaderType));
}

void
VisualEffectInstance::SetShaderTexture(int passIndex,
                                       int textureUnit,
                                       const Texture *texture,
                                       TextureMode textureMode,
                                       unsigned int shaderMask)
{
    FALCON_ENGINE_CHECK_NULLPTR(texture);

    mEffectInstancePassList.at(passIndex)->SetShaderTexture(textureUnit, texture, textureMode, shaderMask);
}

const Sampler *
VisualEffectInstance::GetShaderSampler(int passIndex, int textureUnit) const
{
    return mEffectInstancePassList.at(passIndex)->GetShaderSampler(textureUnit);
}

void
VisualEffectInstance::SetShaderSampler(int passIndex, int textureUnit, const Sampler *sampler,
                                       ShaderType shaderType)
{
    SetShaderSampler(passIndex, textureUnit, sampler, GetShaderMask(shaderType));
}

void
VisualEffectInstance::SetShaderSampler(int passIndex,
                                       int textureUnit,
                                       const Sampler *sampler,
                                       unsigned int shaderMask)
{
    FALCON_ENGINE_CHECK_NULLPTR(sampler);

    mEffectInstancePassList.at(passIndex)->SetShaderSampler(textureUnit, sampler, shaderMask);
}

}
