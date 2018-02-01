#pragma once

#include <FalconEngine/Core/Macro.h>

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

class BlendState;
class CullState;
class DepthTestState;
class OffsetState;
class StencilTestState;
class WireframeState;

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
    SetShader(const std::shared_ptr<Shader>& shader);

    void
    SetBlendState(std::unique_ptr<BlendState> blendStateHandle);

    void
    SetCullState(std::unique_ptr<CullState> cullStateHandle);

    void
    SetDepthTestState(std::unique_ptr<DepthTestState> depthTestStateHandle);

    void
    SetOffsetState(std::unique_ptr<OffsetState> offsetStateHandle);

    void
    SetStencilTestState(std::unique_ptr<StencilTestState> stencilTestStateHandle);

    void
    SetWireframeState(std::unique_ptr<WireframeState> wireframeStateHandle);

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
    std::shared_ptr<Shader> mShader;

    std::unique_ptr<BlendState> mBlendState;
    std::unique_ptr<CullState> mCullState;
    std::unique_ptr<DepthTestState> mDepthTestState;
    std::unique_ptr<OffsetState> mOffsetState;
    std::unique_ptr<StencilTestState> mStencilTestState;
    std::unique_ptr<WireframeState> mWireframeState;
};
#pragma warning(default: 4251)

}
