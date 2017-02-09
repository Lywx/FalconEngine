#include <FalconEngine/Graphics/Renderers/VisualEffectInstance.h>

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

const VisualPass *
VisualEffectInstance::GetPass(int passIndex) const
{
    return mEffect->GetPass(passIndex);
}

ShaderUniform *
VisualEffectInstance::GetShaderUniform(int passIndex, int uniformIndex) const
{
    return mEffect->GetPass(passIndex)->GetShaderUniform(uniformIndex);
}

Texture *
VisualEffectInstance::GetShaderTexture(int passIndex, int textureUnit) const
{
    return mEffect->GetPass(passIndex)->GetShaderTexture(textureUnit);
}

void
VisualEffectInstance::SetShaderTexture(int passIndex, int textureUnit, Texture *texture)
{
    mEffect->GetPass(passIndex)->SetShaderTexture(textureUnit, texture);
}

TextureSampler *
VisualEffectInstance::GetShaderSampler(int passIndex, int textureUnit) const
{
    return mEffect->GetPass(passIndex)->GetShaderSampler(textureUnit);
}

void
VisualEffectInstance::SetShaderSampler(int passIndex, int textureUnit, TextureSampler *sampler)
{
    return mEffect->GetPass(passIndex)->SetShaderSampler(textureUnit, sampler);
}

}
