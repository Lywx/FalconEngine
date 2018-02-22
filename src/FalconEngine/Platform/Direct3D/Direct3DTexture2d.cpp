#include <FalconEngine/Platform/Direct3D/Direct3DTexture2d.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Core/Exception.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture2d.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformTexture2d::PlatformTexture2d(Renderer *renderer, const Texture2d *texture) :
    PlatformTexture(renderer, texture),
    mTextureObj(nullptr),
    mTexturePtr(texture)
{
    auto device = renderer->mData->GetDevice();

    CreateResource(device);
    CreateResourceView(device);
}

PlatformTexture2d::~PlatformTexture2d()
{
}

/************************************************************************/
/* Protected Members                                                    */
/************************************************************************/
void
PlatformTexture2d::CreateResource(ID3D11Device4 *device)
{
    CreateTexture(device);

    mResourceObj = mTextureObj.Get();
}

void
PlatformTexture2d::CreateResourceView(ID3D11Device4 *device)
{
    auto dimension = GetDimension();

    if (mTexturePtr->GetAttachmentEnabled(TextureMode::Color))
    {
        CreateRenderTargetView(device, dimension);
    }

    if (mTexturePtr->GetAttachmentEnabled(TextureMode::DepthStencil))
    {
        CreateDepthStencilView(device, dimension);
    }

    if (mTexturePtr->GetAttachmentEnabled(TextureMode::Image))
    {
        CreateUnorderedAccessView(device, dimension);
    }

    if (mTexturePtr->GetAttachmentEnabled(TextureMode::Texture))
    {
        CreateShaderResourceView(device, dimension);
    }
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
void
PlatformTexture2d::CreateTexture(ID3D11Device4 *device)
{
    D3D11_TEXTURE2D_DESC textureDesc;
    textureDesc.Format = mFormat;
    textureDesc.Usage = mUsage;

    textureDesc.BindFlags = mBindFlag;
    textureDesc.CPUAccessFlags = mCpuFlag;

    textureDesc.Width = mDimension[0];
    textureDesc.Height = mDimension[1];
    textureDesc.ArraySize = mDimension[2];

    // TODO(Wuxiang): Add mipmap support.
    textureDesc.MipLevels = 1;
    textureDesc.MiscFlags = 0;

    // TODO(Wuxiang): Add multisample support.
    textureDesc.SampleDesc.Count = 1;
    textureDesc.SampleDesc.Quality = 0;

    D3D11_SUBRESOURCE_DATA *initialDataAddress = nullptr;
    std::vector<D3D11_SUBRESOURCE_DATA> initialDataList;
    initialDataList.reserve(mDimension[2]);

    auto storageMode = mTexturePtr->GetStorageMode();
    if (storageMode == ResourceStorageMode::Device)
    {
    }
    else if (storageMode == ResourceStorageMode::Host)
    {
        for (int textureIndex = 0; textureIndex < mDimension[2]; ++textureIndex)
        {
            auto textureSlice = mTexturePtr->GetSlice(textureIndex);

            D3D11_SUBRESOURCE_DATA subresourceData;
            subresourceData.pSysMem = textureSlice->GetData();
            // https://msdn.microsoft.com/en-us/library/windows/desktop/ff476220(v=vs.85).aspx
            subresourceData.SysMemPitch = UINT(textureSlice->GetDimension(0) * textureSlice->GetTexelSize());
            subresourceData.SysMemSlicePitch = 0;

            initialDataList.push_back(subresourceData);
        }

        initialDataAddress = initialDataList.data();
    }
    else
    {
        FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
    }

    D3DCheckSuccess(device->CreateTexture2D(&textureDesc, initialDataAddress, mTextureObj.ReleaseAndGetAddressOf()));
}

}

#endif