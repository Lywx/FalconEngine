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

    CreateTexture(device);
    CreateShaderResourceView(device);
}

PlatformTexture2d::~PlatformTexture2d()
{
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
void
PlatformTexture2d::CreateTexture(ID3D11Device4 *device)
{
    D3D11_TEXTURE2D_DESC textureDesc;
    textureDesc.Width = mTexturePtr->mDimension[0];
    textureDesc.Height = mTexturePtr->mDimension[1];

    // TODO(Wuxiang): Add mipmap support.
    textureDesc.MipLevels = 1;
    textureDesc.ArraySize = 1;
    textureDesc.Format = Direct3DResourceFormat[int(mTexturePtr->mFormat)];
    textureDesc.Usage = Direct3DResourceAccessUsage[int(mTexturePtr->mAccessMode)];

    // TODO(Wuxiang): Add vertex stream output support.
    textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

    // TODO(Wuxiang): Add flexible CPU access support.
    textureDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

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