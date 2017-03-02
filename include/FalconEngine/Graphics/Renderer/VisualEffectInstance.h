#pragma once

#include <FalconEngine/GraphicsInclude.h>
#include <FalconEngine/Core/Object.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectInstancePass.h>

namespace FalconEngine
{

class Sampler;
class Texture;

class VisualEffect;
using VisualEffectSharedPtr = std::shared_ptr<VisualEffect>;

template <typename T>
class ShaderUniformValue;

template<typename T>
using ShaderUniformValueSharedPtr = std::shared_ptr<ShaderUniformValue<T>>;

class VisualEffectInstancePass;
using VisualEffectInstancePassUniquePtr = std::unique_ptr<VisualEffectInstancePass>;

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

    VisualEffectInstancePass *
    GetPass(int passIndex);

    template <typename T>
    ShaderUniformValue<T> *
    GetShaderUniform(int passIndex, int uniformIndex);

    template <typename T>
    void
    SetShaderUniform(int passIndex, ShaderUniformValueSharedPtr<T> uniform);

    const Texture *
    GetShaderTexture(int passIndex, int textureUnit) const;

    void
    SetShaderTexture(int passIndex, int textureUnit, const Texture *texture);

    const Sampler *
    GetShaderSampler(int passIndex, int textureUnit) const;

    void
    SetShaderSampler(int passIndex, int textureUnit, const Sampler *sampler);

protected:

    VisualEffectSharedPtr                          mEffect;
    std::vector<VisualEffectInstancePassUniquePtr> mPassList; // Passes contained in this effect.
};

using VisualEffectInstanceSharedPtr = std::shared_ptr<VisualEffectInstance>;

template <typename T>
ShaderUniformValue<T> *
VisualEffectInstance::GetShaderUniform(int passIndex, int uniformIndex)
{
    return mPassList.at(passIndex)->GetShaderUniform(uniformIndex);
}

template <typename T>
void
VisualEffectInstance::SetShaderUniform(int passIndex, ShaderUniformValueSharedPtr<T> uniform)
{
    mPassList.at(passIndex)->SetShaderUniform(uniform);
}

typedef std::shared_ptr<VisualEffectInstance> VisualEffectInstanceSharedPtr;

}
