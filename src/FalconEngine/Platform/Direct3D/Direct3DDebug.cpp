#include <FalconEngine/Platform/Direct3D/Direct3DDebug.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Platform/Win32/Win32Exception.h>

using namespace Microsoft::WRL;

namespace FalconEngine
{

void
Direct3DDebugInitialize(const ComPtr<ID3D11Device>& device)
{
    ComPtr<ID3D11Debug> d3dDebug;
    D3DCheckSuccess(device.As(&d3dDebug));
    ComPtr<ID3D11InfoQueue> d3dInfoQueue;
    D3DCheckSuccess(d3dDebug.As(&d3dInfoQueue));

    // Establish message severity.
    d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
    d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, true);

    // Establish message deny list.
    D3D11_INFO_QUEUE_FILTER filter = {};
    D3D11_MESSAGE_ID hideList[] =
    {
        // TODO: Add more message IDs here as needed.
        D3D11_MESSAGE_ID_SETPRIVATEDATA_CHANGINGPARAMS,
    };
    filter.DenyList.NumIDs = _countof(hideList);
    filter.DenyList.pIDList = hideList;
    d3dInfoQueue->AddStorageFilterEntries(&filter);
}

}

#endif