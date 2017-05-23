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
    mVisualEffect(effect)
{
    for (int i = 0; i < mVisualEffect->GetPassNum(); ++i)
    {
        mVisualEffectInstancePassList.push_back(std::make_unique<VisualEffectInstancePass>(mVisualEffect->GetShader(i)));
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
    return mVisualEffect.get();
}

int
VisualEffectInstance::GetPassNum() const
{
    return mVisualEffect->GetPassNum();
}

VisualEffectInstancePass *
VisualEffectInstance::GetPass(int passIndex)
{
    return mVisualEffectInstancePassList.at(passIndex).get();
}

int
VisualEffectInstance::GetShaderInstancingNum(int passIndex) const
{
    return mVisualEffectInstancePassList.at(passIndex)->GetShaderInstancingNum();
}

void
VisualEffectInstance::SetShaderInstancingNum(int passIndex, int instancingNum)
{
    mVisualEffectInstancePassList.at(passIndex)->SetShaderInstancingNum(instancingNum);
}

const Texture *
VisualEffectInstance::GetShaderTexture(int passIndex, int textureUnit) const
{
    return mVisualEffectInstancePassList.at(passIndex)->GetShaderTexture(textureUnit);
}

void
VisualEffectInstance::SetShaderTexture(int passIndex, int textureUnit, const Texture *texture)
{
    FALCON_ENGINE_CHECK_NULLPTR(texture);

    mVisualEffectInstancePassList.at(passIndex)->SetShaderTexture(textureUnit, texture);
}

const Sampler *
VisualEffectInstance::GetShaderSampler(int passIndex, int textureUnit) const
{
    return mVisualEffectInstancePassList.at(passIndex)->GetShaderSampler(textureUnit);
}

void
VisualEffectInstance::SetShaderSampler(int passIndex, int textureUnit, const Sampler *sampler)
{
    FALCON_ENGINE_CHECK_NULLPTR(sampler);

    mVisualEffectInstancePassList.at(passIndex)->SetShaderSampler(textureUnit, sampler);
}

}
