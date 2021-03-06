#include <FalconEngine/Platform/Direct3D/Direct3DBuffer.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Core/Exception.h>
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
    mUsage = Direct3DResourceAccessUsage[int(mBufferPtr->GetAccessMode())];

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
    FALCON_ENGINE_UNUSE(offset);
    FALCON_ENGINE_UNUSE(size);
}

/************************************************************************/
/* Protected Members                                                    */
/************************************************************************/
void
PlatformBuffer::CreateBuffer(ID3D11Device1 *device)
{
    D3D11_BUFFER_DESC bufferDesc;
    bufferDesc.Usage = mUsage;
    bufferDesc.BindFlags = mBindFlag;
    bufferDesc.CPUAccessFlags = mCpuFlag;

    // TODO(Wuxiang): Add mipmap support.
    // TODO(Wuxiang): Add byte address buffer support.
    // TODO(Wuxiang): Add structured buffer support.
    // https://msdn.microsoft.com/en-us/library/windows/desktop/ff476203(v=vs.85).aspx
    bufferDesc.MiscFlags = 0;

    bufferDesc.ByteWidth = UINT(mBufferPtr->GetCapacitySize());

    // TODO(Wuxiang): Add structured buffer support.
    // https://msdn.microsoft.com/en-us/library/windows/desktop/ff476203(v=vs.85).aspx
    bufferDesc.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA *initialDataAddress = nullptr;
    D3D11_SUBRESOURCE_DATA initialData;
    initialData.pSysMem = mBufferPtr->GetData();
    // NOTE(Wuxiang): Not used in buffer.
    // https://msdn.microsoft.com/en-us/library/windows/desktop/ff476220(v=vs.85).aspx
    initialData.SysMemPitch = 0;
    initialData.SysMemSlicePitch = 0;

    auto storageMode = mBufferPtr->GetStorageMode();
    if (storageMode == ResourceStorageMode::Device)
    {
        // Do nothing.
    }
    else if (storageMode == ResourceStorageMode::Host)
    {
        initialDataAddress = &initialData;
    }
    else
    {
        FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
    }

    D3DCheckSuccess(device->CreateBuffer(&bufferDesc, initialDataAddress, mBufferObj.ReleaseAndGetAddressOf()));
}

void
PlatformBuffer::CreateResource(ID3D11Device1 *device)
{
    CreateBuffer(device);

    mResourceObj = mBufferObj.Get();
}

void
PlatformBuffer::CreateResourceView(ID3D11Device1 *device)
{
    FALCON_ENGINE_UNUSE(device);

    auto bufferType = mBufferPtr->GetBufferType();
    switch (bufferType)
    {
    case BufferType::VertexBuffer:
        return;
    case BufferType::IndexBuffer:
        return;
    case BufferType::ShaderBuffer:
        FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
        break;
    case BufferType::UniformBuffer:
        return;
    case BufferType::TextureBuffer:
        FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
        break;
    case BufferType::FeedbackBuffer:
        FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
        break;
    default:
        FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
    }
}

}

#endif