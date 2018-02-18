#pragma once

#include <FalconEngine/Core/Macro.h>
#include <unordered_map>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Platform/Direct3D/Direct3DLib.h>

namespace FalconEngine
{
class Renderer;

class BlendState;
class CullState;
class DepthTestState;
class OffsetState;
class StencilTestState;
class WireframeState;

// @summary Render state information to avoid redundant state changes.
// @remark Basically, all the draw call's state should be tracked here.
FALCON_ENGINE_CLASS_BEGIN PlatformRendererState
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    PlatformRendererState();
    ~PlatformRendererState() = default;

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Initialize(Renderer * renderer,
               const BlendState * blendState,
               const CullState * cullState,
               const DepthTestState * depthTestState,
               const OffsetState * offsetState,
               const StencilTestState * stencilTestState,
               const WireframeState * wireframeState);

    void
    Set(Renderer * renderer,
        const BlendState * blendState,
        const CullState * cullState,
        const DepthTestState * depthTestState,
        const OffsetState * offsetState,
        const StencilTestState * stencilTestState,
        const WireframeState * wireframeState);

private:
    /************************************************************************/
    /* Private Members                                                      */
    /************************************************************************/
    Microsoft::WRL::ComPtr<ID3D11BlendState1>
    CreateBlendState(ID3D11Device4 * device,
                     const BlendState * blendState);

    Microsoft::WRL::ComPtr<ID3D11DepthStencilState>
    CreateDepthStencilState(ID3D11Device4 * device,
                            const DepthTestState * depthTestState,
                            const StencilTestState * stencilTestState);

    Microsoft::WRL::ComPtr<ID3D11RasterizerState>
    CreateRasterizerState(ID3D11Device4 * device,
                          const CullState * cullState,
                          const OffsetState * offsetState,
                          const WireframeState * wireframeState);

    void
    Validate(Renderer * renderer);

private:
    std::unordered_map<const BlendState *, Microsoft::WRL::ComPtr<ID3D11BlendState1>> mBlendStateTable;
    std::unordered_map<const CullState *, Microsoft::WRL::ComPtr<ID3D11RasterizerState>> mCullStateTable;
    std::unordered_map<const DepthTestState *, Microsoft::WRL::ComPtr<ID3D11DepthStencilState>> mDepthTestStateTable;
    std::unordered_map<const OffsetState *, Microsoft::WRL::ComPtr<ID3D11RasterizerState>> mOffsetStateTable;
    std::unordered_map<const StencilTestState *, Microsoft::WRL::ComPtr<ID3D11DepthStencilState>> mStencilTestStateTable;
    std::unordered_map<const WireframeState *, Microsoft::WRL::ComPtr<ID3D11RasterizerState>> mWireframeStateTable;
};
FALCON_ENGINE_CLASS_END

}

#endif
