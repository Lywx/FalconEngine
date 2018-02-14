#include <FalconEngine/Graphics/Renderer/Renderer.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Core/Exception.h>
#include <FalconEngine/Core/GameEngineDebugger.h>
#include <FalconEngine/Core/GameEnginePlatform.h>
#include <FalconEngine/Core/Utility.h>
#include <FalconEngine/Graphics/Renderer/Primitive.h>
#include <FalconEngine/Graphics/Renderer/Resource/IndexBuffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture2d.h>
#include <FalconEngine/Platform/Direct3D/Direct3DGameEnginePlatformData.h>
#include <FalconEngine/Platform/Direct3D/Direct3DMapping.h>
#include <FalconEngine/Platform/Direct3D/Direct3DRendererData.h>
#include <FalconEngine/Platform/Direct3D/Direct3DRendererState.h>
#include <FalconEngine/Platform/Direct3D/Direct3DTexture2d.h>
#include <FalconEngine/Platform/Win32/Win32Exception.h>
#include <FalconEngine/Platform/Win32/Win32GameEngineWindow.h>

#if defined(FALCON_ENGINE_OS_WINDOWS)
#include <FalconEngine/Platform/Win32/Win32LibCleanEnd.h>
#endif

using namespace Microsoft::WRL;

namespace FalconEngine
{

/************************************************************************/
/* Initialization and Destroy                                           */
/************************************************************************/
void
Renderer::InitializePlatform()
{
    InitializeDataPlatform();
    InitializeStatePlatform();
}

void
Renderer::InitializeDataPlatform()
{
    auto gameEnginePlatform = GameEnginePlatform::GetInstance();

    // Initialize platform renderer data.
    mData = std::unique_ptr<PlatformRendererData, PlatformRendererDataDeleter>(
                new PlatformRendererData(gameEnginePlatform->mData->mContext,
                                         gameEnginePlatform->mData->mDevice,
                                         gameEnginePlatform->mWindow->mHandle),
                PlatformRendererDataDeleter());

    // Fetch context and device.
    auto context = mData->GetContext();
    auto device = mData->GetDeviceCp();

    // Clear the previous window size specific context.
    ID3D11RenderTargetView *nullViews[] = { nullptr };
    context->OMSetRenderTargets(ArraySize(nullViews), nullViews, nullptr);
    context->Flush();

    UINT backBufferWidth = static_cast<UINT>(mWindow.mWidth);
    UINT backBufferHeight = static_cast<UINT>(mWindow.mHeight);
    UINT backBufferCount = 2;
    DXGI_FORMAT backBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM;

    // First, retrieve the underlying DXGI Device from the D3D Device.
    ComPtr<IDXGIDevice4> dxgiDevice;
    D3DCheckSuccess(device.As(&dxgiDevice));

    // Identify the physical adapter (GPU or card) this device is running on.
    ComPtr<IDXGIAdapter> dxgiAdapter;
    D3DCheckSuccess(dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf()));

    // And obtain the factory object that created it.
    ComPtr<IDXGIFactory4> dxgiFactory;
    D3DCheckSuccess(dxgiAdapter->GetParent(IID_PPV_ARGS(dxgiFactory.GetAddressOf())));

    // Create a descriptor for the swap chain.
    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};

    // https://msdn.microsoft.com/en-us/library/windows/desktop/hh404496(v=vs.85).aspx
    swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_IGNORE;
    swapChainDesc.BufferCount = backBufferCount;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

    // https://msdn.microsoft.com/en-us/library/windows/desktop/bb173076(v=vs.85).aspx
    // swapChainDesc.Flags;

    // https://msdn.microsoft.com/en-us/library/windows/desktop/bb173059(v=vs.85).aspx
    swapChainDesc.Format = backBufferFormat;

    // https://msdn.microsoft.com/en-us/library/windows/desktop/bb173076(v=vs.85).aspx
    // swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;

    // https://msdn.microsoft.com/en-us/library/windows/desktop/hh404526(v=vs.85).aspx
    // swapChainDesc.Scaling;

    // https://msdn.microsoft.com/en-us/library/windows/desktop/hh404528(v=vs.85).aspx
    // swapChainDesc.Stereo;

    // https://msdn.microsoft.com/en-us/library/windows/desktop/bb173077(v=vs.85).aspx
    // swapChainDesc.SwapEffect;

    swapChainDesc.Width = backBufferWidth;
    swapChainDesc.Height = backBufferHeight;

    DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsSwapChainDesc = {};

    // https://msdn.microsoft.com/en-us/library/windows/desktop/hh404531(v=vs.85).aspx
    // fsSwapChainDesc.RefreshRate;
    // fsSwapChainDesc.Scaling;
    // fsSwapChainDesc.ScanlineOrdering;
    fsSwapChainDesc.Windowed = TRUE;

    // Create a SwapChain from a Win32 window.
    D3DCheckSuccess(dxgiFactory->CreateSwapChainForHwnd(
                        device.Get(),
                        mData->mWindow,
                        &swapChainDesc,
                        &fsSwapChainDesc,
                        nullptr,
                        mData->mSwapChain.ReleaseAndGetAddressOf()
                    ));

    // This template does not support exclusive fullscreen mode and prevents DXGI from responding to the ALT+ENTER shortcut.
    // https://msdn.microsoft.com/en-us/library/windows/desktop/bb174540(v=vs.85).aspx
    D3DCheckSuccess(dxgiFactory->MakeWindowAssociation(mData->mWindow, DXGI_MWA_NO_ALT_ENTER));

    // Obtain the backbuffer for this window which will be the final 3D rendertarget.
    ComPtr<ID3D11Texture2D> backBuffer;
    D3DCheckSuccess(mData->mSwapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf())));

    // Create a view interface on the rendertarget to use on bind.
    D3DCheckSuccess(device->CreateRenderTargetView(backBuffer.Get(), nullptr, mData->mRenderTargetView.ReleaseAndGetAddressOf()));

    auto depthStencilTexture = std::make_shared<Texture2d>(
                                   backBufferWidth,
                                   backBufferHeight,
                                   TextureFormat::D24_UNORM_S8_UINT,
                                   ResourceCreationAccessMode::GpuReadWrite,
                                   ResourceCreationAccessUsage::Dynamic);
    depthStencilTexture->SetAttachmentEnabled(TextureMode::DepthStencil);
    mData->mDepthStencilTexture = depthStencilTexture;

    Bind(depthStencilTexture.get());
    mData->mDepthStencilView = Get(depthStencilTexture.get())->GetDepthStencilView();

    SetViewportPlatform(mViewport.mLeft, mViewport.mBottom, mViewport.GetWidth(), mViewport.GetHeight(), mViewport.mNear, mViewport.mFar);
}

void
Renderer::InitializeStatePlatform()
{
    // Initialize platform renderer state.
    mState = std::unique_ptr<PlatformRendererState, PlatformRendererStateDeleter>(
                 new PlatformRendererState(),
                 PlatformRendererStateDeleter());

    auto context = mData->GetContext();
    auto device = mData->GetDevice();

    mState->Initialize(context, device,
                       mBlendStateDefault.get(),
                       mCullStateDefault.get(),
                       mDepthTestStateDefault.get(),
                       mOffsetStateDefault.get(),
                       mStencilTestStateDefault.get(),
                       mWireframeStateDefault.get());
}

void
Renderer::DestroyPlatform()
{
    FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
}

/************************************************************************/
/* State Management                                                     */
/************************************************************************/
void
Renderer::SetBlendStatePlatform(const BlendState *blendState)
{
    FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
}

void
Renderer::SetCullStatePlatform(const CullState *cullState)
{
    FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
}

void
Renderer::SetDepthTestStatePlatform(const DepthTestState *depthTestState)
{
    FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
}

void
Renderer::SetOffsetStatePlatform(const OffsetState *offsetState)
{
    FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
}

void
Renderer::SetStencilTestStatePlatform(const StencilTestState *stencilTestState)
{
    FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
}

void
Renderer::SetWireframeStatePlatform(const WireframeState *wireframeState)
{
    FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
}

/************************************************************************/
/* Viewport Management                                                  */
/************************************************************************/
void
Renderer::SetViewportPlatform(float x, float y, float width, float height, float near, float far)
{
    auto context = mData->GetContext();
    CD3D11_VIEWPORT viewport(x, y, width, height, near, far);
    context->RSSetViewports(1, &viewport);
}

/************************************************************************/
/* Window Management                                                    */
/************************************************************************/
void
Renderer::SetWindowPlatform(int width, int height)
{
    // TODO(Wuxiang): This would need to recreate all the resource on the fly. I should implement this later.
    FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
}

/************************************************************************/
/* Framebuffer Management                                               */
/************************************************************************/
void
Renderer::ClearColorBufferPlatform(const Vector4f& color)
{
    auto context = mData->GetContext();
    context->ClearRenderTargetView(mData->mRenderTargetView.Get(), color.Data());
    context->OMSetRenderTargets(1, mData->mRenderTargetView.GetAddressOf(), mData->mDepthStencilView.Get());
}

void
Renderer::ClearDepthBufferPlatform(float depth)
{
    auto context = mData->GetContext();
    context->ClearDepthStencilView(mData->mDepthStencilView.Get(), D3D11_CLEAR_DEPTH, depth, 0);
    context->OMSetRenderTargets(1, mData->mRenderTargetView.GetAddressOf(), mData->mDepthStencilView.Get());
}

void
Renderer::ClearStencilBufferPlatform(unsigned int stencil)
{
    auto context = mData->GetContext();
    context->ClearDepthStencilView(mData->mDepthStencilView.Get(), D3D11_CLEAR_STENCIL, 1.0f, UINT8(stencil));
    context->OMSetRenderTargets(1, mData->mRenderTargetView.GetAddressOf(), mData->mDepthStencilView.Get());
}

void
Renderer::ClearFrameBufferPlatform(const Vector4f& color, float depth, unsigned int stencil)
{
    auto context = mData->GetContext();
    context->ClearRenderTargetView(mData->mRenderTargetView.Get(), color.Data());
    context->ClearDepthStencilView(mData->mDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, depth, UINT8(stencil));
    context->OMSetRenderTargets(1, mData->mRenderTargetView.GetAddressOf(), mData->mDepthStencilView.Get());
}

void
Renderer::RecoverDeviceLostPlatform()
{
    // TODO(Wuxiang): Most of the games have issues with device lost. You might consider to recover from that.
    // https://answers.ea.com/t5/Dragon-Age-Inquisition/DirectX-function-GetDeviceRemovedReason-failed-with-dxgi-error/td-p/4008007
    // https://gamedev.stackexchange.com/questions/126534/dx11-handle-device-removed
}

void
Renderer::SwapFrameBufferPlatform()
{
    // https://msdn.microsoft.com/en-us/library/windows/desktop/bb174576(v=vs.85).aspx
    HRESULT result = mData->mSwapChain->Present(1, 0);
    // If the device was reset we must completely reinitialize the renderer.
    if (result == DXGI_ERROR_DEVICE_REMOVED || result == DXGI_ERROR_DEVICE_RESET)
    {
#if defined(FALCON_ENGINE_DEBUG_GRAPHICS)
        auto device = mData->GetDevice();
        // https://msdn.microsoft.com/en-us/library/windows/desktop/ff476526(v=vs.85).aspx
        GameEngineDebugger::OutputStringFormat("Device Lost: Reason code 0x%08X\n", result == DXGI_ERROR_DEVICE_REMOVED ? device->GetDeviceRemovedReason() : result);
#endif
        // If the device was removed for any reason, a new device
        // and swap chain will need to be created.
        RecoverDeviceLostPlatform();
    }
    else
    {
        D3DCheckSuccess(result);
    }
}

void
Renderer::DrawPrimitivePlatform(const Primitive *primitive, int primitiveInstancingNum)
{
    FALCON_ENGINE_CHECK_NULLPTR(primitive);

    PrimitiveType primitiveType = primitive->GetPrimitiveType();
    const D3D11_PRIMITIVE_TOPOLOGY primitiveMode = Direct3DPrimitiveType[int(primitiveType)];
    auto vertexNum = primitive->GetVertexNum();
    auto vertexOffset = primitive->GetVertexOffset();

    if (vertexNum < 1)
    {
        return;
    }

    auto context = mData->GetContext();
    context->IASetPrimitiveTopology(primitiveMode);

    if (primitiveType == PrimitiveType::Point)
    {
        context->DrawInstanced(vertexNum, primitiveInstancingNum, vertexOffset, 0);
    }
    else if (primitiveType == PrimitiveType::Line)
    {
        context->DrawInstanced(vertexNum, primitiveInstancingNum, vertexOffset, 0);
    }
    else if (primitiveType == PrimitiveType::LineStrip)
    {
        context->DrawInstanced(vertexNum, primitiveInstancingNum, vertexOffset, 0);
    }
    else if (primitiveType == PrimitiveType::Triangle)
    {
        // When use index buffer
        auto indexBuffer = primitive->GetIndexBuffer();
        if (indexBuffer)
        {
            auto indexNum = indexBuffer->GetElementNum();
            if (indexNum < 1)
            {
                return;
            }

            auto indexOffset = primitive->GetIndexOffset();
            context->DrawIndexedInstanced(indexNum, primitiveInstancingNum, indexOffset, 0, 0);
        }
        else
        {
            context->DrawInstanced(vertexNum, primitiveInstancingNum, vertexOffset, 0);
        }
    }
    else
    {
        FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
    }
}

}

#endif