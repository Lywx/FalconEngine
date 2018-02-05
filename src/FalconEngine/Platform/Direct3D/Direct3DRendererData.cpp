#include <FalconEngine/Platform/Direct3D/Direct3DRendererData.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Platform/Win32/Win32Exception.h>

using namespace Microsoft::WRL;

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformRendererData::PlatformRendererData(
    const Microsoft::WRL::ComPtr<ID3D11DeviceContext4>& context,
    const Microsoft::WRL::ComPtr<ID3D11Device4>& device,
    const HWND& window)
    : mWindow(window)
{
    // NOTE(Wuxiang): Because the Direct3D device might be lost during running,
    // we need to record them as weak reference.
    context.AsWeak(&mContext);
    device.AsWeak(&mDevice);
}

PlatformRendererData::~PlatformRendererData()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
ID3D11DeviceContext4 *
PlatformRendererData::GetContext()
{
    return GetContextCp().Get();
}

Microsoft::WRL::ComPtr<ID3D11DeviceContext4>
PlatformRendererData::GetContextCp()
{
    ComPtr<ID3D11DeviceContext4> context;
    mContext.As<ID3D11DeviceContext4>(&context);
    return context;
}

ID3D11Device4 *
PlatformRendererData::GetDevice()
{
    return GetDeviceCp().Get();
}

Microsoft::WRL::ComPtr<ID3D11Device4>
PlatformRendererData::GetDeviceCp()
{
    ComPtr<ID3D11Device4> device;
    mDevice.As<ID3D11Device4>(&device);
    return device;
}

}

#endif