#include <FalconEngine/Platform/Direct3D/Direct3DRendererState.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Graphics/Renderer/Renderer.h>
#include <FalconEngine/Graphics/Renderer/State/BlendState.h>
#include <FalconEngine/Graphics/Renderer/State/CullState.h>
#include <FalconEngine/Graphics/Renderer/State/DepthTestState.h>
#include <FalconEngine/Graphics/Renderer/State/OffsetState.h>
#include <FalconEngine/Graphics/Renderer/State/StencilTestState.h>
#include <FalconEngine/Graphics/Renderer/State/WireframeState.h>
#include <FalconEngine/Platform/Direct3D/Direct3DMapping.h>
#include <FalconEngine/Platform/Direct3D/Direct3DRendererData.h>

namespace FalconEngine
{

FALCON_ENGINE_DELETER_IMPLEMENT(PlatformRendererState, PlatformRendererStateDeleter);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformRendererState::PlatformRendererState()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformRendererState::Initialize(Renderer *renderer,
                                  const BlendState *blendState,
                                  const CullState *cullState,
                                  const DepthTestState *depthTestState,
                                  const OffsetState *offsetState,
                                  const StencilTestState *stencilTestState,
                                  const WireframeState *wireframeState)
{
    Set(renderer, blendState, cullState, depthTestState, offsetState, stencilTestState, wireframeState);
}

void
PlatformRendererState::Set(Renderer *renderer,
                           const BlendState *blendState,
                           const CullState *cullState,
                           const DepthTestState *depthTestState,
                           const OffsetState *offsetState,
                           const StencilTestState *stencilTestState,
                           const WireframeState *wireframeState)
{
    auto context = renderer->mData->GetContext();
    auto device = renderer->mData->GetDevice();

    Microsoft::WRL::ComPtr<ID3D11BlendState1> blendStatePlatform;
    {
        auto iter = mBlendStateTable.find(blendState);
        if (iter != mBlendStateTable.end())
        {
            blendStatePlatform = iter->second;
        }
        else
        {
            // NOTE(Wuxiang): D3D Blend State consists of FE Blend State.
            blendStatePlatform = CreateBlendState(device, blendState);
            mBlendStateTable[blendState] = blendStatePlatform;
        }
    }
    // NEW(Wuxiang): Add alpha to coverage support.
    context->OMSetBlendState(blendStatePlatform.Get(), blendState->mConstantFactor.Data(), 0xffffffff);

    Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStatePlatform;
    {
        auto iter = mDepthTestStateTable.find(depthTestState);
        if (iter != mDepthTestStateTable.end())
        {
            depthStencilStatePlatform = iter->second;
        }
        else
        {
            // NOTE(Wuxiang): D3D Depth Stencil State consists of FE Depth Test State and Stencil Test State.
            depthStencilStatePlatform = CreateDepthStencilState(device, depthTestState, stencilTestState);
            mDepthTestStateTable[depthTestState] = depthStencilStatePlatform;
            mStencilTestStateTable[stencilTestState] = depthStencilStatePlatform;
        }
    }
    context->OMSetDepthStencilState(depthStencilStatePlatform.Get(), stencilTestState->mCompareReference);

    Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStatePlatform;
    {
        auto iter = mCullStateTable.find(cullState);
        if (iter != mCullStateTable.end())
        {
            rasterizerStatePlatform = iter->second;
        }
        else
        {
            // NOTE(Wuxiang): D3D Rasterizer State consists of FE Cull State, Offset State and Wireframe State.
            rasterizerStatePlatform = CreateRasterizerState(device, cullState, offsetState, wireframeState);
            mCullStateTable[cullState] = rasterizerStatePlatform;
            mOffsetStateTable[offsetState] = rasterizerStatePlatform;
            mWireframeStateTable[wireframeState] = rasterizerStatePlatform;
        }
    }
    context->RSSetState(rasterizerStatePlatform.Get());
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
Microsoft::WRL::ComPtr<ID3D11BlendState1>
PlatformRendererState::CreateBlendState(
    ID3D11Device4 *device,
    const BlendState *blendState)
{
    D3D11_BLEND_DESC1 blendDesc;
    ZeroMemory(&blendDesc, sizeof blendDesc);

    // NEW(Wuxiang): Add alpha to coverage support.
    blendDesc.AlphaToCoverageEnable = false;
    // NEW(Wuxiang): Support MRT blending.
    blendDesc.IndependentBlendEnable = false;

    D3D11_RENDER_TARGET_BLEND_DESC1 blendDescRt;
    ZeroMemory(&blendDescRt, sizeof blendDescRt);
    blendDescRt.BlendEnable = blendState->mEnabled;
    blendDescRt.BlendOp = Direct3DBlendOperator[BlendOperatorIndex(blendState->mOperator)];
    blendDescRt.BlendOpAlpha = Direct3DBlendOperator[BlendOperatorIndex(blendState->mOperatorAlpha)];;
    blendDescRt.SrcBlend = Direct3DBlendFactor[BlendFactorIndex(blendState->mSourceFactor)];
    blendDescRt.SrcBlendAlpha = Direct3DBlendFactor[BlendFactorIndex(blendState->mSourceFactorAlpha)];;
    blendDescRt.DestBlend = Direct3DBlendFactor[BlendFactorIndex(blendState->mDestinationFactor)];
    blendDescRt.DestBlendAlpha = Direct3DBlendFactor[BlendFactorIndex(blendState->mDestinationFactorAlpha)];

    blendDescRt.LogicOpEnable = blendState->mLogicEnabled;
    blendDescRt.LogicOp = Direct3DLogicOperator[LogicOperatorIndex(blendState->mLogicOperator)];

    blendDescRt.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    blendDesc.RenderTarget[0] = blendDescRt;

    Microsoft::WRL::ComPtr<ID3D11BlendState1> blendStatePlatform;
    device->CreateBlendState1(&blendDesc, blendStatePlatform.ReleaseAndGetAddressOf());
    return blendStatePlatform;
}

void
SetStencilTestFaceStatePlatform(_IN_ const StencilTestFaceState& faceStateCurrent,
                                _OUT_ D3D11_DEPTH_STENCILOP_DESC& faceStatePlatform)
{
    faceStatePlatform.StencilDepthFailOp = Direct3DStencilOperation[StencilOperationIndex(faceStateCurrent.mDepthTestFailOperation)];
    faceStatePlatform.StencilFailOp = Direct3DStencilOperation[StencilOperationIndex(faceStateCurrent.mStencilTestFailOperation)];
    faceStatePlatform.StencilPassOp = Direct3DStencilOperation[StencilOperationIndex(faceStateCurrent.mDepthTestPassOperation)];
    faceStatePlatform.StencilFunc = Direct3DStencilFunction[StencilFunctionIndex(faceStateCurrent.mStencilCompareFunction)];
}

Microsoft::WRL::ComPtr<ID3D11DepthStencilState>
PlatformRendererState::CreateDepthStencilState(
    ID3D11Device4 *device,
    const DepthTestState *depthTestState,
    const StencilTestState *stencilTestState)
{
    D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
    ZeroMemory(&depthStencilDesc, sizeof depthStencilDesc);
    depthStencilDesc.DepthEnable = depthTestState->mEnabled;
    depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK(int(depthTestState->mWriteEnabled));
    depthStencilDesc.DepthFunc = Direct3DDepthFunction[DepthFunctionIndex(depthTestState->mCompareFunction)];

    depthStencilDesc.StencilEnable = stencilTestState->mEnabled;
    depthStencilDesc.StencilReadMask = stencilTestState->mCompareMask;
    depthStencilDesc.StencilWriteMask = stencilTestState->mWriteMask;
    SetStencilTestFaceStatePlatform(stencilTestState->mFrontFace, depthStencilDesc.FrontFace);
    SetStencilTestFaceStatePlatform(stencilTestState->mBackFace, depthStencilDesc.BackFace);

    Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilState;
    device->CreateDepthStencilState(&depthStencilDesc, depthStencilState.ReleaseAndGetAddressOf());
    return depthStencilState;
}

Microsoft::WRL::ComPtr<ID3D11RasterizerState>
PlatformRendererState::CreateRasterizerState(
    ID3D11Device4 *device,
    const CullState *cullState,
    const OffsetState *offsetState,
    const WireframeState *wireframeState)
{
    D3D11_RASTERIZER_DESC rasterizerDesc;
    ZeroMemory(&rasterizerDesc, sizeof rasterizerDesc);

    // NEW(Wuxiang): Add line anti-aliasing support.
    rasterizerDesc.AntialiasedLineEnable = false;

    if (wireframeState->mEnabled)
    {
        rasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;
    }
    else
    {
        rasterizerDesc.FillMode = D3D11_FILL_SOLID;
    }

    if (cullState->mEnabled)
    {
        if (cullState->mCounterClockwise)
        {
            rasterizerDesc.CullMode = D3D11_CULL_FRONT;
        }
        else
        {
            rasterizerDesc.CullMode = D3D11_CULL_BACK;
        }
    }
    else
    {
        rasterizerDesc.CullMode = D3D11_CULL_NONE;
    }

    rasterizerDesc.FrontCounterClockwise = true;

    // https://msdn.microsoft.com/en-us/library/windows/desktop/cc308048(v=vs.85).aspx
    rasterizerDesc.DepthBias = INT(offsetState->mBiasUnit);
    rasterizerDesc.DepthBiasClamp = 0.0f;
    rasterizerDesc.SlopeScaledDepthBias = offsetState->mBiasFactor;

    rasterizerDesc.DepthClipEnable = true;

    // NEW(Wuxiang): Added scissor test support.
    rasterizerDesc.ScissorEnable = false;

    // NEW(Wuxiang): Added multisample support.
    rasterizerDesc.MultisampleEnable = false;

    Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerState;
    device->CreateRasterizerState(&rasterizerDesc, rasterizerState.ReleaseAndGetAddressOf());
    return rasterizerState;
}

void
PlatformRendererState::Validate(Renderer *)
{
}

}

#endif