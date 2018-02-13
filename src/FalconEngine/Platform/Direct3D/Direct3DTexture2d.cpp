#include <FalconEngine/Platform/Direct3D/Direct3DTexture2d.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
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

    mResourceObj = mTextureObj;
}

void
PlatformTexture2d::CreateResourceView(ID3D11Device4 *device)
{
    auto dimension = GetDimension();

    if (mTexturePtr->mAttachment[int(TextureMode::Color)])
    {
        CreateRenderTargetView(device, dimension);
    }

    if (mTexturePtr->mAttachment[int(TextureMode::DepthStencil)])
    {
        CreateDepthStencilView(device, dimension);
    }

    if (mTexturePtr->mAttachment[int(TextureMode::Image)])
    {
        CreateUnorderedAccessView(device, dimension);
    }

    if (mTexturePtr->mAttachment[int(TextureMode::Texture)])
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

    D3D11_SUBRESOURCE_DATA subresourceData;
    subresourceData.pSysMem = mTexturePtr->mData;
    subresourceData.SysMemPitch = UINT(mTexturePtr->mDataSize);
    subresourceData.SysMemSlicePitch = 0;
    D3DCheckSuccess(device->CreateTexture2D(&textureDesc, &subresourceData, &mTextureObj));
}

}

#endif