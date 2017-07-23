#pragma once

#include <FalconEngine/Graphics/Common.h>

#include <memory>
#include <map>
#include <vector>

#include <FalconEngine/Graphics/Renderer/State/BlendState.h>
#include <FalconEngine/Graphics/Renderer/State/CullState.h>
#include <FalconEngine/Graphics/Renderer/State/DepthTestState.h>
#include <FalconEngine/Graphics/Renderer/State/OffsetState.h>
#include <FalconEngine/Graphics/Renderer/State/StencilTestState.h>
#include <FalconEngine/Graphics/Renderer/State/WireframeState.h>

namespace FalconEngine
{

class Sampler;
class Texture;

class Shader;
using ShaderSharedPtr = std::shared_ptr<Shader>;

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

#pragma warning(disable: 4251)
class FALCON_ENGINE_API VisualEffectPass final
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    VisualEffectPass();
    ~VisualEffectPass();

    VisualEffectPass(const VisualEffectPass& rhs) = delete;
    VisualEffectPass& operator=(const VisualEffectPass& rhs) = delete;

    VisualEffectPass(VisualEffectPass&& rhs) noexcept = default;
    VisualEffectPass& operator=(VisualEffectPass&& rhs) noexcept = default;

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

    BlendState *
    GetBlendState();

    const BlendState *
    GetBlendState() const;

    const CullState *
    GetCullState() const;

    CullState *
    GetCullState();

    const DepthTestState *
    GetDepthTestState() const;

    DepthTestState *
    GetDepthTestState();

    const OffsetState *
    GetOffsetState() const;

    OffsetState *
    GetOffsetState();

    const StencilTestState *
    GetStencilTestState() const;

    StencilTestState *
    GetStencilTestState();

    const WireframeState *
    GetWireframeState() const;

    WireframeState *
    GetWireframeState();

protected:
    ShaderSharedPtr           mShader;

    BlendStateUniquePtr       mBlendState;
    CullStateUniquePtr        mCullState;
    DepthTestStateUniquePtr   mDepthTestState;
    OffsetStateUniquePtr      mOffsetState;
    StencilTestStateUniquePtr mStencilTestState;
    WireframeStateUniquePtr   mWireframeState;
};
#pragma warning(default: 4251)

}
