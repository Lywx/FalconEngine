#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <memory>
#include <FalconEngine/Platform/Direct3D/Direct3DLib.h>

namespace FalconEngine
{

FALCON_ENGINE_CLASS_BEGIN PlatformRendererData final
{
public:
    explicit PlatformRendererData(const Microsoft::WRL::ComPtr<ID3D11DeviceContext4>& context,
                                  const Microsoft::WRL::ComPtr<ID3D11Device4>&        device,
                                  const HWND &                                        window);
    ~PlatformRendererData();

public:
    ID3D11DeviceContext4 *
    GetContext();

    Microsoft::WRL::ComPtr<ID3D11DeviceContext4>
    GetContextCp();

    ID3D11Device4 *
    GetDevice();

    Microsoft::WRL::ComPtr<ID3D11Device4>
    GetDeviceCp();

public:
    HWND                                           mWindow;

    Microsoft::WRL::ComPtr<IDXGISwapChain1>        m_swapChain;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargetView;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depthStencilView;

private:
    Microsoft::WRL::WeakRef                        mContext;
    Microsoft::WRL::WeakRef                        mDevice;
};
FALCON_ENGINE_CLASS_END

}
#endif
