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
/* Public Members                                                       */
/************************************************************************/
void *
PlatformTexture2d::Map(Renderer *renderer, ResourceMapAccessMode access, ResourceMapFlushMode flush,
                       ResourceMapSyncMode synchronization, int64_t offset, int64_t size)
{
    return PlatformTexture::Map<ID3D11Texture2D>(renderer, mTextureObj, access, flush, sync, offset, size);
}

void
PlatformTexture2d::Unmap(Renderer *renderer)
{
    return PlatformTexture::Unmap<ID3D11Texture2D>(renderer, mTextureObj);
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
    textureDesc.Format = Direct3DTextureFormat[int(mTexturePtr->mFormat)];
    textureDesc.Usage = Direct3DResourceUsage[int(mTexturePtr->mAccessMode)];

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

void
PlatformTexture2d::CreateShaderResourceView(ID3D11Device4 *device)
{
    D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
    shaderResourceViewDesc.Format = Direct3DTextureFormat[int(mTexturePtr->mFormat)];
    shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;

    // TODO(Wuxiang): Add mipmap support.
    shaderResourceViewDesc.Texture2D.MipLevels = 1;
    shaderResourceViewDesc.Texture2D.MostDetailedMip = 1;
    D3DCheckSuccess(device->CreateShaderResourceView(mTextureObj, &shaderResourceViewDesc, &mShaderResourceView));
}

void
PlatformTexture2d::CreateRenderTargetView(ID3D11Device4 *device)
{
    D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
    renderTargetViewDesc.Format = Direct3DTextureFormat[int(mTexturePtr->mFormat)];
    renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

    // TODO(Wuxiang): Add mipmap support.
    renderTargetViewDesc.Texture2D.MipSlice = 0;
    D3DCheckSuccess(device->CreateRenderTargetView(mTextureObj, &renderTargetViewDesc, &mRenderTargetView));

}
}

#endif