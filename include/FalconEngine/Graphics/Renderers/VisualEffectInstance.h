#pragma once

#include <FalconEngine/Graphics/GraphicsInclude.h>
#include <FalconEngine/Graphics/Renderers/VisualEffect.h>
#include <FalconEngine/Graphics/Renderers/VisualPass.h>
#include <FalconEngine/Graphics/Renderers/Resources/Texture.h>
#include <FalconEngine/Graphics/Renderers/Resources/TextureSampler.h>

namespace FalconEngine
{

class VisualEffectInstance : public Object
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    VisualEffectInstance(VisualEffectSharedPtr effect);
    virtual ~VisualEffectInstance();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    const VisualEffect *
    GetEffect() const;

    int
    GetPassNum() const;

    const VisualPass *
    GetPass(int passIndex) const;

    ShaderUniform *
    GetShaderUniform(int passIndex, int uniformIndex) const;

    template <typename T>
    void
    SetShaderUniform(int passIndex, ShaderUniformValue<T> *shaderUniform);

    Texture *
    GetShaderTexture(int passIndex, int textureUnit) const;

    void
    SetShaderTexture(int passIndex, int textureUnit, Texture *texture);

    TextureSampler *
    GetShaderSampler(int passIndex, int textureUnit) const;

    void
    SetShaderSampler(int passIndex, int textureUnit, TextureSampler *sampler);

protected:
    VisualEffectSharedPtr mEffect;
};

template <typename T>
void
VisualEffectInstance::SetShaderUniform(int passIndex, ShaderUniformValue<T> *shaderUniform)
{
    return mEffect->GetPass(passIndex)->SetShaderUniform(shaderUniform);
}

typedef std::shared_ptr<VisualEffectInstance> VisualEffectInstanceSharedPtr;

}
