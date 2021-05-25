#include <FalconEngine/Platform/Direct3D/Direct3DRendererData.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Core/Memory.h>
#include <FalconEngine/Platform/Win32/Win32Exception.h>

using namespace Microsoft::WRL;

namespace FalconEngine
{

FALCON_ENGINE_DELETER_DECLARE(PlatformRendererData, PlatformRendererDataDeleter);
FALCON_ENGINE_DELETER_IMPLEMENT(PlatformRendererData, PlatformRendererDataDeleter);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformRendererData::PlatformRendererData(
    const ComPtr<ID3D11DeviceContext1>& context,
    const ComPtr<ID3D11Device1>& device,
    const HWND& window) :
    mContext(context),
    mDevice(device),
    mWindow(window)
{
}

PlatformRendererData::~PlatformRendererData()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
ID3D11DeviceContext1 *
PlatformRendererData::GetContext()
{
    return mContext.Get();
}

Microsoft::WRL::ComPtr<ID3D11DeviceContext1>
PlatformRendererData::GetContextCp()
{
    return mContext;
}

ID3D11Device1 *
PlatformRendererData::GetDevice()
{
    return mDevice.Get();
}

Microsoft::WRL::ComPtr<ID3D11Device1>
PlatformRendererData::GetDeviceCp()
{
    return mDevice;
}

}

#endif