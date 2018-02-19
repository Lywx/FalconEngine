#pragma once

#include <FalconEngine/Core/Macro.h>

#include <memory>
#include <vector>

#include <FalconEngine/Core/Object.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectInstancePass.h>
#include <FalconEngine/Graphics/Renderer/Shader/Shader.h>

namespace FalconEngine
{

class Sampler;
class Texture;

template <typename T>
class ShaderUniformValue;

class VisualEffect;
class VisualEffectInstancePass;

// @summary Represents a visual effect instance. This class may contain some
// asset, like material, texture etc. This class is typically used inside a scene
// class. Once the scene is loaded then the instance is initialized and disposed when
// the scene is disposed. So as the asset used in this effect instance, though the
// asset is disposed by manually calling asset manager.
FALCON_ENGINE_CLASS_BEGIN VisualEffectInstance final
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    VisualEffectInstance(const std::shared_ptr<VisualEffect>& effect);
    ~VisualEffectInstance();

    // NOTE(Wuxiang): unique_ptr is not allowed to copy.
    VisualEffectInstance(const VisualEffectInstance & rhs) = delete;
    VisualEffectInstance& operator=(const VisualEffectInstance & rhs) = delete;

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    const VisualEffect *
    GetEffect() const;

    VisualEffect *
    GetEffect();

    int
    GetPassNum() const;

    VisualEffectInstancePass *
    GetPass(int passIndex);

    int
    GetShaderInstancingNum(int passIndex) const;

    void
    SetShaderInstancingNum(int passIndex, int instancingNum);

    template <typename T>
    ShaderUniformValue<T> *
    GetShaderUniform(int passIndex, int uniformIndex);

    template <typename T>
    void
    SetShaderUniform(int passIndex,
                     std::shared_ptr<ShaderUniformValue<T>> uniform);

    template <typename T>
    void
    SetShaderUniformBuffer(int passIndex,
                           const std::string & uniformBufferName,
                           size_t uniformBufferSize);

    const Texture *
    GetShaderTexture(int passIndex, int textureUnit) const;

    void
    SetShaderTexture(int passIndex,
                     int textureUnit,
                     const Texture * texture,
                     TextureMode textureMode,
                     ShaderType shaderType);

    void
    SetShaderTexture(int passIndex,
                     int textureUnit,
                     const Texture * texture,
                     TextureMode textureMode,
                     unsigned int shaderMask);

    const Sampler *
    GetShaderSampler(int passIndex, int textureUnit) const;

    void
    SetShaderSampler(int passIndex, int textureUnit, const Sampler * sampler, ShaderType shaderType);

    void
    SetShaderSampler(int passIndex, int textureUnit, const Sampler * sampler, unsigned int shaderMask);

protected:
    std::shared_ptr<VisualEffect> mEffect;
    std::vector<std::unique_ptr<VisualEffectInstancePass>> mEffectInstancePassList; // Passes contained in this effect instance.
};
FALCON_ENGINE_CLASS_END

template <typename T>
ShaderUniformValue<T> *
VisualEffectInstance::GetShaderUniform(int passIndex, int uniformIndex)
{
    return mEffectInstancePassList.at(passIndex)->GetShaderUniform(uniformIndex);
}

template <typename T>
void
VisualEffectInstance::SetShaderUniform(int passIndex,
                                       std::shared_ptr<ShaderUniformValue<T>> uniform)
{
    FALCON_ENGINE_CHECK_NULLPTR(uniform);

    mEffectInstancePassList.at(passIndex)->SetShaderUniform(uniform);
}

}
