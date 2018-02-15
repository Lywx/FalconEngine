#include <FalconEngine/Platform/Direct3D/Direct3DRendererState.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Graphics/Renderer/State/BlendState.h>
#include <FalconEngine/Graphics/Renderer/State/CullState.h>
#include <FalconEngine/Graphics/Renderer/State/DepthTestState.h>
#include <FalconEngine/Graphics/Renderer/State/OffsetState.h>
#include <FalconEngine/Graphics/Renderer/State/StencilTestState.h>
#include <FalconEngine/Graphics/Renderer/State/WireframeState.h>
#include <FalconEngine/Platform/Direct3D/Direct3DMapping.h>

namespace FalconEngine
{

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
PlatformRendererState::Initialize(ID3D11DeviceContext4 *context,
                                  ID3D11Device4 *device,
                                  const BlendState *blendState,
                                  const CullState *cullState,
                                  const DepthTestState *depthTestState,
                                  const OffsetState *offsetState,
                                  const StencilTestState *stencilTestState,
                                  const WireframeState *wireframeState)
{
    // Blend State
    CreateBlendState(device, blendState);

    // NEW(Wuxiang): Add alpha to coverage support.
    context->OMSetBlendState(mBlendState.Get(), blendState->mConstantFactor.Data(), 0xffffffff);

    // Depth Stencil State
    CreateDepthStencilState(device, depthTestState, stencilTestState);

    context->OMSetDepthStencilState(mDepthStencilState.Get(), stencilTestState->mCompareReference);

    // Rasterizer State

    D3D11_RASTERIZER_DESC rasterizerDesc;
    ZeroMemory(&rasterizerDesc, sizeof rasterizerDesc);
    rasterizerDesc.AntialiasedLineEnable = false;
    rasterizerDesc.CullMode = D3D11_CULL_BACK;
    rasterizerDesc.FillMode = D3D11_FILL_SOLID;
    rasterizerDesc.FrontCounterClockwise = false;
    rasterizerDesc.DepthBias = 0;
    rasterizerDesc.DepthBiasClamp = 0.0f;
    rasterizerDesc.DepthClipEnable = true;
    rasterizerDesc.ScissorEnable = false;
    rasterizerDesc.MultisampleEnable = false;
    device->CreateRasterizerState(&rasterizerDesc, mRasterizerState.ReleaseAndGetAddressOf());
    context->RSSetState(mRasterizerState.Get());
}

void
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
    device->CreateBlendState1(&blendDesc, mBlendState.ReleaseAndGetAddressOf());
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

void
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

    device->CreateDepthStencilState(&depthStencilDesc, mDepthStencilState.ReleaseAndGetAddressOf());
}

}

#endif