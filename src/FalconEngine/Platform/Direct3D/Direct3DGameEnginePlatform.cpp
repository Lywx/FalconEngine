#include <FalconEngine/Core/GameEnginePlatform.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Core/GameEngineSettings.h>
#include <FalconEngine/Platform/Direct3D/Direct3DGameEnginePlatformData.h>
#include <FalconEngine/Platform/Direct3D/Direct3DLib.h>
#include <FalconEngine/Platform/Win32/Win32Exception.h>

using namespace Microsoft::WRL;
using namespace std;

namespace FalconEngine
{

void
GameEnginePlatform::InitializeContextPlatform()
{
    UINT creationFlags = 0;

    // https://blogs.msdn.microsoft.com/chuckw/2012/11/30/direct3d-sdk-debug-layer-tricks/
#if defined(FALCON_ENGINE_DEBUG_GRAPHICS)
    creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    static const D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_9_3,
        D3D_FEATURE_LEVEL_9_2,
        D3D_FEATURE_LEVEL_9_1,
    };

    // Create the DX11 API device object, and get a corresponding context.
    ComPtr<ID3D11Device> device;
    ComPtr<ID3D11DeviceContext> context;
    D3DCheckSuccess(
        D3D11CreateDevice(
            nullptr,                            // specify nullptr to use the default adapter
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            creationFlags,
            featureLevels,
            _countof(featureLevels),
            D3D11_SDK_VERSION,
            device.ReleaseAndGetAddressOf(),    // returns the Direct3D device created
            &mData->mFeatureLevel,              // returns feature level of device created
            context.ReleaseAndGetAddressOf()    // returns the device immediate context
        ));

    D3DCheckSuccess(context.As(&mData->mContext));
    D3DCheckSuccess(device.As(&mData->mDevice));
}

void
GameEnginePlatform::InitializeDataPlatform()
{
    mData = std::unique_ptr<PlatformGameEnginePlatformData, PlatformGameEnginePlatformDataDeleter>(
            new PlatformGameEnginePlatformData(),
            PlatformGameEnginePlatformDataDeleter());
}

void
GameEnginePlatform::InitializeLoaderPlatform()
{
}

}

#endif