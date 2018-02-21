#pragma once

#include <FalconEngine/Core/Macro.h>

#include <memory>
#include <map>
#include <vector>

#include <FalconEngine/Graphics/Renderer/Resource/VertexFormat.h>
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

FALCON_ENGINE_CLASS_BEGIN VisualEffectPass final
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    VisualEffectPass();
    ~VisualEffectPass();

    VisualEffectPass(const VisualEffectPass & rhs) = delete;
    VisualEffectPass& operator=(const VisualEffectPass & rhs) = delete;

    VisualEffectPass(VisualEffectPass&& rhs) noexcept = default;
    VisualEffectPass& operator=(VisualEffectPass&& rhs) noexcept = default;

public:
    /************************************************************************/
    /* Shader Management                                                    */
    /************************************************************************/
    const Shader *
    GetShader() const;

    Shader *
    GetShader();

    void
    SetShader(std::shared_ptr<Shader> shader);

    const VertexFormat *
    GetShaderVertexFormat() const;

    VertexFormat *
    GetShaderVertexFormat();

    std::shared_ptr<VertexFormat>
    GetShaderVertexFormatSp();

    void
    SetShaderVertexFormat(std::shared_ptr<VertexFormat> shaderVertexFormat);

    /************************************************************************/
    /* State Management                                                     */
    /************************************************************************/
    const BlendState *
    GetBlendState() const;

    BlendState *
    GetBlendState();

    void
    SetBlendState(std::unique_ptr<BlendState> blendStateHandle);

    const CullState *
    GetCullState() const;

    CullState *
    GetCullState();

    void
    SetCullState(std::unique_ptr<CullState> cullStateHandle);

    const DepthTestState *
    GetDepthTestState() const;

    DepthTestState *
    GetDepthTestState();

    void
    SetDepthTestState(std::unique_ptr<DepthTestState> depthTestStateHandle);

    const OffsetState *
    GetOffsetState() const;

    OffsetState *
    GetOffsetState();

    void
    SetOffsetState(std::unique_ptr<OffsetState> offsetStateHandle);

    const StencilTestState *
    GetStencilTestState() const;

    StencilTestState *
    GetStencilTestState();

    void
    SetStencilTestState(std::unique_ptr<StencilTestState> stencilTestStateHandle);

    const WireframeState *
    GetWireframeState() const;

    WireframeState *
    GetWireframeState();

    void
    SetWireframeState(std::unique_ptr<WireframeState> wireframeStateHandle);

private:
    /************************************************************************/
    /* Shader Members                                                       */
    /************************************************************************/
    std::shared_ptr<Shader> mShader;
    std::shared_ptr<VertexFormat> mShaderVertexFormat;

    /************************************************************************/
    /* State Members                                                        */
    /************************************************************************/
    std::unique_ptr<BlendState> mBlendState;
    std::unique_ptr<CullState> mCullState;
    std::unique_ptr<DepthTestState> mDepthTestState;
    std::unique_ptr<OffsetState> mOffsetState;
    std::unique_ptr<StencilTestState> mStencilTestState;
    std::unique_ptr<WireframeState> mWireframeState;
};
FALCON_ENGINE_CLASS_END

}
