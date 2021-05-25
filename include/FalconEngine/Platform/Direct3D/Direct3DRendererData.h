#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <memory>

#include <FalconEngine/Platform/Direct3D/Direct3DLib.h>

namespace FalconEngine
{
class Texture2d;

FALCON_ENGINE_CLASS_BEGIN PlatformRendererData final
{
public:
    explicit PlatformRendererData(const Microsoft::WRL::ComPtr<ID3D11DeviceContext1>& context,
                                  const Microsoft::WRL::ComPtr<ID3D11Device1>& device,
                                  const HWND & window);
    ~PlatformRendererData();

public:
    ID3D11DeviceContext1 *
    GetContext();

    Microsoft::WRL::ComPtr<ID3D11DeviceContext1>
    GetContextCp();

    ID3D11Device1 *
    GetDevice();

    Microsoft::WRL::ComPtr<ID3D11Device1>
    GetDeviceCp();

public:
    std::shared_ptr<Texture2d> mDepthStencilTexture;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthStencilView;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView;
    Microsoft::WRL::ComPtr<IDXGISwapChain1> mSwapChain;

private:
    Microsoft::WRL::ComPtr<ID3D11DeviceContext1> mContext;
    Microsoft::WRL::ComPtr<ID3D11Device1> mDevice;

public:
    HWND mWindow;
};
FALCON_ENGINE_CLASS_END

}
#endif
