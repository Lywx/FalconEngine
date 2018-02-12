#include <FalconEngine/Platform/Direct3D/Direct3DTexture2dArray.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformTexture2dArray::PlatformTexture2dArray(Renderer *renderer, const Texture2dArray *textureArray) :
    PlatformTexture2d(renderer, textureArray),
    mTextureObj(nullptr),
    mTexturePtr(textureArray)
{
}

PlatformTexture2dArray::~PlatformTexture2dArray()
{
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
void
PlatformTexture2dArray::CreateTexture(ID3D11Device4 *device)
{
    D3D11_TEXTURE2D_DESC textureDesc;
    textureDesc.Format = mFormat;
    textureDesc.Usage = mUsage;

    textureDesc.BindFlags = Direct3DResourceBindFlag(mTexturePtr);
    textureDesc.CPUAccessFlags = Direct3DResourceAccessFlag(mTexturePtr->mAccessMode);

    textureDesc.Width = mDimension[0];
    textureDesc.Height = mDimension[1];
    textureDesc.ArraySize = mDimension[2];

    // TODO(Wuxiang): Add mipmap support.
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