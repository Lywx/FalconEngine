#pragma once

#include <FalconEngine/GraphicsInclude.h>

#include <memory>
#include <map>
#include <vector>

namespace FalconEngine
{

class Sampler;
using SamplerMap = std::map<int, const Sampler *>;

class Texture;
using TextureMap = std::map<int, const Texture *>;

class Shader;
using ShaderSharedPtr = std::shared_ptr<Shader>;

class ShaderUniform;
using ShaderUniformSharedPtr = std::shared_ptr<ShaderUniform>;
using ShaderUniformSharedPtrVector = std::vector<ShaderUniformSharedPtr>;

class BlendState;
using BlendStateUniquePtr = std::unique_ptr<BlendState>;

class CullState;
using CullStateUniquePtr = std::unique_ptr<CullState>;

class DepthTestState;
using DepthTestStateUniquePtr = std::unique_ptr<DepthTestState>;

class OffsetState;
using OffsetStateUniquePtr = std::unique_ptr<OffsetState>;

class StencilTestState;
using StencilTestStateUniquePtr = std::unique_ptr<StencilTestState>;

class WireframeState;
using WireframeStateUniquePtr = std::unique_ptr<WireframeState>;

class VisualPass
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    VisualPass();
    virtual ~VisualPass();

public:
    void
    SetShader(ShaderSharedPtr shader);

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

    void
    SetBlendState(BlendStateUniquePtr blendStateHandle);

    void
    SetCullState(CullStateUniquePtr cullStateHandle);

    void
    SetDepthTestState(DepthTestStateUniquePtr depthTestStateHandle);

    void
    SetOffsetState(OffsetStateUniquePtr offsetStateHandle);

    void
    SetStencilTestState(StencilTestStateUniquePtr stencilTestStateHandle);

    void
    SetWireframeState(WireframeStateUniquePtr wireframeStateHandle);

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

    const BlendState *
    GetBlendState() const;

    const CullState *
    GetCullState() const;

    const DepthTestState *
    GetDepthTestState() const;

    const OffsetState *
    GetOffsetState() const;

    const StencilTestState *
    GetStencilTestState() const;

    const WireframeState *
    GetWireframeState() const;

protected:
    ShaderSharedPtr              mShader;
    ShaderUniformSharedPtrVector mShaderUniformList;
    TextureMap                   mShaderTextureTable;
    SamplerMap                   mShaderSamplerTable;

    BlendStateUniquePtr       mBlendStateHandle;
    CullStateUniquePtr        mCullStateHandle;
    DepthTestStateUniquePtr   mDepthTestStateHandle;
    OffsetStateUniquePtr      mOffsetStateHandle;
    StencilTestStateUniquePtr mStencilTestStateHandle;
    WireframeStateUniquePtr   mWireframeStateHandle;

    friend class Renderer;
};

}
