#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Platform/Direct3D/Direct3DLib.h>

namespace FalconEngine
{

class BlendState;
class CullState;
class DepthTestState;
class OffsetState;
class StencilTestState;
class WireframeState;

// @summary Render state information to avoid redundant state changes.
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
    Initialize(ID3D11DeviceContext4 * context,
               ID3D11Device4 * device,
               const BlendState * blendState,
               const CullState * cullState,
               const DepthTestState * depthTestState,
               const OffsetState * offsetState,
               const StencilTestState * stencilTestState,
               const WireframeState * wireframeState);

    void
    CreateBlendState(ID3D11Device4 * device,
                     const BlendState * blendState);

    void
    CreateDepthStencilState(ID3D11Device4 * device,
                            const DepthTestState * depthTestState,
                            const StencilTestState * stencilTestState);

    void
    CreateRasterizerState(ID3D11Device4 * device);

public:
    Microsoft::WRL::ComPtr<ID3D11BlendState1> mBlendState;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilState> mDepthStencilState;
    Microsoft::WRL::ComPtr<ID3D11RasterizerState> mRasterizerState;
};

FALCON_ENGINE_CLASS_END

}

#endif
