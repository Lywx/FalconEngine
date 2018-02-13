#include <FalconEngine/Platform/Direct3D/Direct3DBuffer.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Graphics/Renderer/Renderer.h>
#include <FalconEngine/Platform/Direct3D/Direct3DRendererData.h>
#include <FalconEngine/Platform/Win32/Win32Exception.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformBuffer::PlatformBuffer(Renderer *renderer, const Buffer *buffer) :
    PlatformResource(renderer, buffer),
    mBufferObj(nullptr),
    mBufferPtr(buffer)
{
    mBindFlag = Direct3DResourceBindFlag(mBufferPtr);
    mCpuFlag = Direct3DResourceAccessFlag(mBufferPtr->GetAccessMode());

    auto device = renderer->mData->GetDevice();

    CreateResource(device);
    CreateResourceView(device);
}

PlatformBuffer::~PlatformBuffer()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformBuffer::Flush(Renderer *, int64_t offset, int64_t size)
{
    _UNUSED(offset);
    _UNUSED(size);
}

/************************************************************************/
/* Protected Members                                                    */
/************************************************************************/
void
PlatformBuffer::CreateBuffer(ID3D11Device4 *device)
{
    D3D11_BUFFER_DESC bufferDesc;
    bufferDesc.Usage = mUsage;;
    bufferDesc.BindFlags = mBindFlag;
    bufferDesc.CPUAccessFlags = mCpuFlag;

    // TODO(Wuxiang): Add mipmap support.
    // TODO(Wuxiang): Add byte address buffer support.
    // TODO(Wuxiang): Add structured buffer support.
    // https://msdn.microsoft.com/en-us/library/windows/desktop/ff476203(v=vs.85).aspx
    bufferDesc.MiscFlags = 0;

    bufferDesc.ByteWidth = mBufferPtr->GetCapacitySize();

    // TODO(Wuxiang): Add structured buffer support.
    // https://msdn.microsoft.com/en-us/library/windows/desktop/ff476203(v=vs.85).aspx
    bufferDesc.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA subresourceData;

    auto storageMode = mBufferPtr->GetStorageMode();
    if (storageMode == ResourceStorageMode::Device)
    {
        subresourceData.pSysMem = nullptr;

        // NOTE(Wuxiang): Not used in buffer.
        // https://msdn.microsoft.com/en-us/library/windows/desktop/ff476220(v=vs.85).aspx
        subresourceData.SysMemPitch = 0;
        subresourceData.SysMemSlicePitch = 0;
    }
    else if (storageMode == ResourceStorageMode::Host)
    {
        subresourceData.pSysMem = mBufferPtr->GetData();

        // NOTE(Wuxiang): Not used in buffer.
        // https://msdn.microsoft.com/en-us/library/windows/desktop/ff476220(v=vs.85).aspx
        subresourceData.SysMemPitch = 0;
        subresourceData.SysMemSlicePitch = 0;
    }
    else
    {
        FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
    }

    D3DCheckSuccess(device->CreateBuffer(&bufferDesc, &subresourceData, &mBufferObj));
}

void
PlatformBuffer::CreateResource(ID3D11Device4 *device)
{
    CreateBuffer(device);

    mResourceObj = mBufferObj;
}

}

#endif