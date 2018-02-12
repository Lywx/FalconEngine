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

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
void
PlatformTexture2d::CreateTexture(ID3D11Device4 *device)
{
    D3D11_TEXTURE2D_DESC textureDesc;
    textureDesc.Format = mFormat;
    textureDesc.Usage = mUsage;

    textureDesc.BindFlags = Direct3DResourceBindFlag(mTexturePtr);
    textureDesc.CPUAccessFlags = Direct3DResourceAccessFlag(mTexturePtr->mAccessMode);

    textureDesc.Width = mDimension[0];
    textureDesc.Height = mDimension[1];

    // TODO(Wuxiang): Add mipmap support.
    textureDesc.ArraySize = 1;
    textureDesc.MipLevels = 1;

    // TODO(Wuxiang): Add mipmap support.
    textureDesc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA subresourceData;
    subresourceData.pSysMem = mTexturePtr->mData;
    subresourceData.SysMemPitch = mTexturePtr->mDataSize;
    subresourceData.SysMemSlicePitch = 0;
    D3DCheckSuccess(device->CreateTexture2D(&textureDesc, &subresourceData, &mTextureObj));
}

}

#endif