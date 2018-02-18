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
    Initialize(ID3D11DeviceContext4 * context,
               ID3D11Device4 * device,
               const BlendState * blendState,
               const CullState * cullState,
               const DepthTestState * depthTestState,
               const OffsetState * offsetState,
               const StencilTestState * stencilTestState,
               const WireframeState * wireframeState);

    void
    Set(const BlendState * blendState);

    void
    Set(const CullState * cullState);

    void
    Set(const DepthTestState * depthTestState);

    void
    Set(const OffsetState * offsetState);

    void
    Set(const StencilTestState * stencilTestState);

    void
    Set(const WireframeState * wireframeState);

private:
    void
    CreateBlendState(ID3D11Device4 * device,
                     const BlendState * blendState);

    void
    CreateDepthStencilState(ID3D11Device4 * device,
                            const DepthTestState * depthTestState,
                            const StencilTestState * stencilTestState);

    void
    CreateRasterizerState(ID3D11Device4 * device,
                          const CullState * cullState,
                          const OffsetState * offsetState,
                          const WireframeState * wireframeState);

private:
    Microsoft::WRL::ComPtr<ID3D11BlendState1> mBlendState;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilState> mDepthStencilState;
    Microsoft::WRL::ComPtr<ID3D11RasterizerState> mRasterizerState;
};
FALCON_ENGINE_CLASS_END

}

#endif
