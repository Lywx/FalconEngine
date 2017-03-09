#include <FalconEngine/Graphics/Renderer/VisualEffectInstancePass.h>

#include <FalconEngine/Graphics/Renderer/Shader/Shader.h>
#include <FalconEngine/Graphics/Renderer/Shader/ShaderUniform.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
VisualEffectInstancePass::VisualEffectInstancePass(Shader *shader) :
    mShader(shader)
{
}

VisualEffectInstancePass::~VisualEffectInstancePass()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
VisualEffectInstancePass::SetShaderUniform(ShaderUniformSharedPtr shaderUniform)
{
    if (mShader->ContainUniform(shaderUniform->mName))
    {
        mShaderUniformList.push_back(shaderUniform);
    }
    else
    {
        mShader->PushUniform(shaderUniform->mName, shaderUniform->mType);
    }
}

void
VisualEffectInstancePass::SetShaderTexture(int textureUnit, const Texture *texture)
{
    FALCON_ENGINE_CHECK_NULLPTR(texture);

    mShaderTextureTable[textureUnit] = texture;
}

void
VisualEffectInstancePass::SetShaderSampler(int textureUnit, const Sampler *sampler)
{
    FALCON_ENGINE_CHECK_NULLPTR(sampler);

    mShaderSamplerTable[textureUnit] = sampler;
}

Shader *
VisualEffectInstancePass::GetShader() const
{
    return mShader;
}

int
VisualEffectInstancePass::GetShaderUniformNum() const
{
    return int(mShaderUniformList.size());
}

ShaderUniform *
VisualEffectInstancePass::GetShaderUniform(int uniformIndex) const
{
    return mShaderUniformList.at(uniformIndex).get();
}

int
VisualEffectInstancePass::GetShaderTextureNum() const
{
    return int(mShaderTextureTable.size());
}

const Texture *
VisualEffectInstancePass::GetShaderTexture(int textureUnit) const
{
    return mShaderTextureTable.at(textureUnit);
}

int
VisualEffectInstancePass::GetShaderSamplerNum() const
{
    return int(mShaderSamplerTable.size());
}

const Sampler *
VisualEffectInstancePass::GetShaderSampler(int textureUnit)
{
    return mShaderSamplerTable.at(textureUnit);
}
}
