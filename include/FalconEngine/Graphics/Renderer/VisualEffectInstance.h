#pragma once

#include <FalconEngine/Core/Common.h>

#include <vector>

#include <FalconEngine/Core/Object.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectInstancePass.h>

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
#pragma warning(disable: 4251)
class FALCON_ENGINE_API VisualEffectInstance : public Object
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    VisualEffectInstance(std::shared_ptr<VisualEffect> effect);
    virtual ~VisualEffectInstance();

    // NOTE(Wuxiang): unique_ptr is not allowed to copy.
    VisualEffectInstance(const VisualEffectInstance& rhs) = delete;
    VisualEffectInstance& operator=(const VisualEffectInstance& rhs) = delete;

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

    int
    GetShaderInstancingNum(int passIndex) const;

    void
    SetShaderInstancingNum(int passIndex, int instancingNum);

    template <typename T>
    ShaderUniformValue<T> *
    GetShaderUniform(int passIndex, int uniformIndex);

    template <typename T>
    void
    SetShaderUniform(int passIndex, std::shared_ptr<ShaderUniformValue<T>> uniform);

    const Texture *
    GetShaderTexture(int passIndex, int textureUnit) const;

    void
    SetShaderTexture(int passIndex, int textureUnit, const Texture *texture);

    const Sampler *
    GetShaderSampler(int passIndex, int textureUnit) const;

    void
    SetShaderSampler(int passIndex, int textureUnit, const Sampler *sampler);

protected:
    std::shared_ptr<VisualEffect>                          mEffect;
    std::vector<std::unique_ptr<VisualEffectInstancePass>> mEffectInstancePassList; // Passes contained in this effect instance.
};
#pragma warning(default: 4251)

template <typename T>
ShaderUniformValue<T> *
VisualEffectInstance::GetShaderUniform(int passIndex, int uniformIndex)
{
    return mEffectInstancePassList.at(passIndex)->GetShaderUniform(uniformIndex);
}

template <typename T>
void
VisualEffectInstance::SetShaderUniform(int passIndex, std::shared_ptr<ShaderUniformValue<T>> uniform)
{
    FALCON_ENGINE_CHECK_NULLPTR(uniform);

    mEffectInstancePassList.at(passIndex)->SetShaderUniform(uniform);
}

}
