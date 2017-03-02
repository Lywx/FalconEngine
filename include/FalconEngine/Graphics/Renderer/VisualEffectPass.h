#pragma once

#include <FalconEngine/GraphicsInclude.h>

#include <memory>
#include <map>
#include <vector>

namespace FalconEngine
{

class Sampler;
class Texture;

class Shader;
using ShaderSharedPtr = std::shared_ptr<Shader>;

class ShaderUniform;
using ShaderUniformSharedPtr = std::shared_ptr<ShaderUniform>;

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

class VisualEffectPass sealed
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    VisualEffectPass();
    ~VisualEffectPass();

public:
    void
    SetShader(ShaderSharedPtr shader);

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

    const Shader *
    GetShader() const;

    Shader *
    GetShader();

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

    BlendStateUniquePtr       mBlendState;
    CullStateUniquePtr        mCullState;
    DepthTestStateUniquePtr   mDepthTestState;
    OffsetStateUniquePtr      mOffsetState;
    StencilTestStateUniquePtr mStencilTestState;
    WireframeStateUniquePtr   mWireframeState;
};

}
