#include <FalconEngine/Graphics/Renderer/VisualEffectInstance.h>
#include <FalconEngine/Graphics/Renderer/VisualEffect.h>
#include <FalconEngine/Graphics/Renderer/VisualPass.h>
#include <FalconEngine/Graphics/Renderer/Resources/Texture.h>
#include <FalconEngine/Graphics/Renderer/Resources/Sampler.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
VisualEffectInstance::VisualEffectInstance(VisualEffectSharedPtr effect) :
    mEffect(effect)
{
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

VisualPass *
VisualEffectInstance::GetPass(int passIndex)
{
    return mEffect->GetPass(passIndex);
}

const Texture *
VisualEffectInstance::GetShaderTexture(int passIndex, int textureUnit) const
{
    return mEffect->GetPass(passIndex)->GetShaderTexture(textureUnit);
}

void
VisualEffectInstance::SetShaderTexture(int passIndex, int textureUnit, const Texture *texture)
{
    mEffect->GetPass(passIndex)->SetShaderTexture(textureUnit, texture);
}

const Sampler *
VisualEffectInstance::GetShaderSampler(int passIndex, int textureUnit) const
{
    return mEffect->GetPass(passIndex)->GetShaderSampler(textureUnit);
}

void
VisualEffectInstance::SetShaderSampler(int passIndex, int textureUnit, const Sampler *sampler)
{
    return mEffect->GetPass(passIndex)->SetShaderSampler(textureUnit, sampler);
}

}
