#pragma once

#include <FalconEngine/Core/Macro.h>

#include <algorithm>
#include <map>
#include <memory>
#include <vector>

#include <FalconEngine/Graphics/Renderer/Resource/Texture.h>
#include <FalconEngine/Graphics/Renderer/Resource/TextureAttachment.h>
#include <FalconEngine/Graphics/Renderer/Resource/SamplerAttachment.h>

namespace FalconEngine
{

class Sampler;
class Shader;
class ShaderUniform;
class Texture;

FALCON_ENGINE_CLASS_BEGIN VisualEffectInstancePass final
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit VisualEffectInstancePass(Shader * shader);
    ~VisualEffectInstancePass();

    VisualEffectInstancePass(const VisualEffectInstancePass&) = delete;
    VisualEffectInstancePass& operator=(const VisualEffectInstancePass&) = delete;

    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    // @summary The shader uniform table that consists of all the needed update
    // uniform value.
    //
    // @remark The shader uniform table between pass should not allow sharing
    // uniform table. This is because all the passes may be generated before
    // actually drawing so that sharing uniform table might overwrite previously
    // unsynchronized value.
    void
    SetShaderUniform(std::shared_ptr<ShaderUniform> shaderUniform);

    void
    SetShaderUniformBuffer(int shaderUniform);

    void
    SetShaderTexture(int textureUnit,
                     const Texture * texture,
                     TextureMode textureMode,
                     unsigned textureShaderMask);

    void
    SetShaderSampler(int textureUnit,
                     const Sampler * sampler,
                     unsigned int samplerShaderMask);

    Shader *
    GetShader() const;

    int
    GetShaderInstancingNum() const;

    void
    SetShaderInstancingNum(int instancingNum);

    int
    GetShaderUniformNum() const;

    ShaderUniform *
    GetShaderUniform(int uniformIndex) const;

    auto GetShaderTextureBegin() const
    {
        return mShaderTextureTable.cbegin();
    }

    auto GetShaderTextureEnd() const
    {
        return mShaderTextureTable.cend();
    }

    auto GetShaderTextureBegin()
    {
        return mShaderTextureTable.begin();
    }

    auto GetShaderTextureEnd()
    {
        return mShaderTextureTable.end();
    }

    int
    GetShaderTextureNum() const;

    const Texture *
    GetShaderTexture(int textureUnit) const;

    auto GetShaderSamplerBegin() const
    {
        return mShaderSamplerTable.cbegin();
    }

    auto GetShaderSamplerEnd() const
    {
        return mShaderSamplerTable.cend();
    }

    auto GetShaderSamplerBegin()
    {
        return mShaderSamplerTable.begin();
    }

    auto GetShaderSamplerEnd()
    {
        return mShaderSamplerTable.end();
    }

    int
    GetShaderSamplerNum() const;

    const Sampler *
    GetShaderSampler(int textureUnit);

private:
    // NOTE(Wuxiang): The instance pass will not manage the lifetime of the shader.
    // Shader's lifetime is managed by the VisualPass class, which is further
    // managed by VisualEffect. So when VisualEffect is disposed the shader is
    // disposed (if disposed already by AssetManager). The relation could be
    // represented as:
    //
    // 1. AssetManager -> Shader
    // 2. VisualEffect -> VisualPass -> Shader
    // 3. VisualEffectInstance -> VisualEffect
    //
    // Since the VisaulEffectInstance has influence over the shader and it controls
    // VisualEffectInstancePass as well, if the VisaulEffectInstance is disposed,
    // VisualEffectInstancePass must be disposed before.
    //
    // So there is no way for dangling pointer to affect this 'mShader' field.
    Shader                                     *mShader;
    int                                         mShaderInstancingNum;
    std::map<int, SamplerAttachment>            mShaderSamplerTable;
    std::map<int, TextureAttachment>            mShaderTextureTable;
    std::vector<std::shared_ptr<ShaderUniform>> mShaderUniformList;
};
FALCON_ENGINE_CLASS_END

}
