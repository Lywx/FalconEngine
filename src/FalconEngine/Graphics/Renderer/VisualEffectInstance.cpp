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
VisualEffectInstance::VisualEffectInstance(VisualEffectSharedPtr effect) :
    mEffect(effect)
{
    for (int i = 0; i < mEffect->GetPassNum(); ++i)
    {
        mPassList.push_back(std::make_unique<VisualEffectInstancePass>(mEffect->GetShader(i)));
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
    return mPassList.at(passIndex).get();
}

const Texture *
VisualEffectInstance::GetShaderTexture(int passIndex, int textureUnit) const
{
    return mPassList.at(passIndex)->GetShaderTexture(textureUnit);
}

void
VisualEffectInstance::SetShaderTexture(int passIndex, int textureUnit, const Texture *texture)
{
    FALCON_ENGINE_CHECK_NULLPTR(texture);

    mPassList.at(passIndex)->SetShaderTexture(textureUnit, texture);
}

const Sampler *
VisualEffectInstance::GetShaderSampler(int passIndex, int textureUnit) const
{
    return mPassList.at(passIndex)->GetShaderSampler(textureUnit);
}

void
VisualEffectInstance::SetShaderSampler(int passIndex, int textureUnit, const Sampler *sampler)
{
    FALCON_ENGINE_CHECK_NULLPTR(sampler);

    mPassList.at(passIndex)->SetShaderSampler(textureUnit, sampler);
}

}
