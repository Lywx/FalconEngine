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
class Uniform;
class UniformBuffer;
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
    int
    GetInstancingNum() const;

    void
    SetInstancingNum(int instancingNum);

    auto GetSamplerBegin() const
    {
        return mSamplerTable.cbegin();
    }

    auto GetSamplerEnd() const
    {
        return mSamplerTable.cend();
    }

    auto GetSamplerBegin()
    {
        return mSamplerTable.begin();
    }

    auto GetSamplerEnd()
    {
        return mSamplerTable.end();
    }

    int
    GetSamplerNum() const;

    const Sampler *
    GetSampler(int textureUnit);

    void
    SetSampler(int textureUnit,
               const Sampler * sampler,
               unsigned int samplerShaderMask);

    Shader *
    GetShader() const;

    auto GetTextureBegin() const
    {
        return mTextureTable.cbegin();
    }

    auto GetTextureEnd() const
    {
        return mTextureTable.cend();
    }

    auto GetTextureBegin()
    {
        return mTextureTable.begin();
    }

    auto GetTextureEnd()
    {
        return mTextureTable.end();
    }

    int
    GetTextureNum() const;

    const Texture *
    GetTexture(int textureUnit) const;

    void
    SetTexture(int textureUnit,
               const Texture * texture,
               TextureMode textureMode,
               unsigned textureShaderMask);

    Uniform *
    GetUniform(int uniformIndex);

    int
    GetUniformNum() const;

    // @summary The shader uniform table that consists of all the needed update
    // uniform value.
    //
    // @remark The shader uniform table between pass should not allow sharing
    // uniform table. This is because all the passes may be generated before
    // actually drawing so that sharing uniform table might overwrite previously
    // unsynchronized value.
    void
    SetUniform(std::shared_ptr<Uniform> uniform);

    void
    SetUniformBuffer(std::shared_ptr<UniformBuffer> uniformBuffer);

    UniformBuffer *
    GetUniformBuffer(int uniformBufferIndex);

    int
    GetUniformBufferNum() const;

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
    int mInstancingNum;
    Shader *mShader;
    std::map<int, SamplerAttachment> mSamplerTable;
    std::map<int, TextureAttachment> mTextureTable;
    std::vector<std::shared_ptr<Uniform>> mUniformList;
    std::vector<std::shared_ptr<UniformBuffer>> mUniformBufferList;
};
FALCON_ENGINE_CLASS_END

}
