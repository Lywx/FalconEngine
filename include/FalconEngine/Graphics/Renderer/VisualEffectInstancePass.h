#pragma once

#include <FalconEngine/GraphicsInclude.h>

#include <map>
#include <vector>

namespace FalconEngine
{

class Shader;

class Sampler;
using SamplerMap = std::map<int, const Sampler *>;

class ShaderUniform;
using ShaderUniformSharedPtr = std::shared_ptr<ShaderUniform>;

class Texture;

class VisualEffectInstancePass final
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit VisualEffectInstancePass(Shader *shader);
    ~VisualEffectInstancePass();

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
    SetShaderUniform(ShaderUniformSharedPtr shaderUniform);

    void
    SetShaderTexture(int textureUnit, const Texture *texture);

    void
    SetShaderSampler(int textureUnit, const Sampler *sampler);

    Shader *
    GetShader() const;

    int
    GetShaderUniformNum() const;

    ShaderUniform *
    GetShaderUniform(int uniformIndex) const;

    int
    GetShaderTextureNum() const;

    const Texture *
    GetShaderTexture(int textureUnit) const;

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
    Shader                             *mShader;
    std::vector<ShaderUniformSharedPtr> mShaderUniformList;

    std::map<int, const Texture *>      mShaderTextureTable;
    SamplerMap                          mShaderSamplerTable;

    friend class Renderer;
};

}
