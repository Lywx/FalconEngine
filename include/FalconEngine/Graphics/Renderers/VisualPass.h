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
#include <FalconEngine/Graphics/Renderers/Resources/TextureSampler.h>
#include <FalconEngine/Graphics/Shaders/Shader.h>

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
    SetShaderTexture(int textureUnit, Texture *texture);

    void
    SetShaderSampler(int textureUnit, TextureSampler *sampler);

    void
    SetBlendState(BlendStateHandle blendStateHandle);

    void
    SetCullState(CullStateHandle cullStateHandle);

    void
    SetDepthTestState(DepthTestStateHandle depthTestStateHandle);

    void
    SetOffsetState(OffsetStateHandle offsetStateHandle);

    void
    SetStencilTestState(StencilTestStateHandle stencilTestStateHandle);

    void
    SetWireframeState(WireframeStateHandle wireframeStateHandle);

    Shader *
    GetShader() const;

    int
    GetShaderUniformNum() const;

    ShaderUniform *
    GetShaderUniform(int uniformIndex) const;

    int
    GetShaderTextureNum() const;

    Texture *
    GetShaderTexture(int textureUnit) const;

    int
    GetShaderSamplerNum() const;

    TextureSampler *
    GetShaderSampler(int textureUnit);

    BlendState *
    GetBlendState() const;

    CullState *
    GetCullState() const;

    DepthTestState *
    GetDepthTestState() const;

    OffsetState *
    GetOffsetState() const;

    StencilTestState *
    GetStencilTestState() const;

    WireframeState *
    GetWireframeState() const;

protected:
    ShaderSharedPtr              mShader;
    ShaderUniformVector    mShaderUniformVector;
    TextureTable           mShaderTextureTable;
    TextureSamplerTable    mShaderSamplerTable;

    BlendStateHandle       mBlendStateHandle;
    CullStateHandle        mCullStateHandle;
    DepthTestStateHandle   mDepthTestStateHandle;
    OffsetStateHandle      mOffsetStateHandle;
    StencilTestStateHandle mStencilTestStateHandle;
    WireframeStateHandle   mWireframeStateHandle;

    friend class Renderer;
};

typedef std::unique_ptr<VisualPass>   VisualPassHandle;
typedef std::vector<VisualPassHandle> VisualPassHandleVector;

}
