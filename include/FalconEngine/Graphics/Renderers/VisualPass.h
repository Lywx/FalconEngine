#pragma once

#include <FalconEngine/Graphics/GraphicsInclude.h>

#include <memory>

#include <FalconEngine/Graphics/Renderers/States/BlendState.h>
#include <FalconEngine/Graphics/Renderers/States/CullState.h>
#include <FalconEngine/Graphics/Renderers/States/DepthTestState.h>
#include <FalconEngine/Graphics/Renderers/States/OffsetState.h>
#include <FalconEngine/Graphics/Renderers/States/StencilTestState.h>
#include <FalconEngine/Graphics/Renderers/States/WireframeState.h>
#include <FalconEngine/Graphics/Renderers/Resources/Texture.h>
#include <FalconEngine/Graphics/Renderers/Resources/Sampler.h>
#include <FalconEngine/Graphics/Renderers/Shaders/Shader.h>

namespace FalconEngine
{

class VisualPass : public Object
{
    FALCON_ENGINE_RTTI_DECLARE;

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
    SetShaderUniform(ShaderUniform *shaderUniform);

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
    ShaderSharedPtr           mShader;
    ShaderUniformPtrVector    mShaderUniformVector;
    TextureTable              mShaderTextureTable;
    SamplerTable              mShaderSamplerTable;

    BlendStateUniquePtr       mBlendStateHandle;
    CullStateUniquePtr        mCullStateHandle;
    DepthTestStateUniquePtr   mDepthTestStateHandle;
    OffsetStateUniquePtr      mOffsetStateHandle;
    StencilTestStateUniquePtr mStencilTestStateHandle;
    WireframeStateUniquePtr   mWireframeStateHandle;

    friend class Renderer;
};

using VisualPassUniquePtr = std::unique_ptr<VisualPass>;
using VisualPassUniquePtrVector = std::vector<VisualPassUniquePtr>;

}
