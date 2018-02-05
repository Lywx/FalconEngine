#include <FalconEngine/Platform/Direct3D/Direct3DTexture1d.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Graphics/Renderer/Resource/Texture1d.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformTexture1d::PlatformTexture1d(Renderer *renderer, const Texture1d *texture) :
    PlatformTexture(renderer, texture),
    mTextureObj(nullptr),
    mTexturePtr(texture)
{
    auto device = renderer->mData->GetDevice();

    CreateTexture(device);
    CreateShaderResourceView(device);
}

PlatformTexture1d::~PlatformTexture1d()
{
    mTextureObj->Release();
    mShaderResourceView->Release();
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void *
PlatformTexture1d::Map(Renderer *renderer, ResourceMapAccessMode access, ResourceMapFlushMode flush,
                       ResourceMapSyncMode synchronization, int64_t offset, int64_t size)
{
    return PlatformTexture::Map<ID3D11Texture1D>(renderer, mTextureObj, access, flush, sync, offset, size);
}

void
PlatformTexture1d::Unmap(Renderer *renderer)
{
    return PlatformTexture::Unmap<ID3D11Texture1D>(renderer, mTextureObj);
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
void
PlatformTexture1d::CreateTexture(ID3D11Device4 *device)
{
    D3D11_TEXTURE1D_DESC textureDesc;
    textureDesc.Width = mTexturePtr->mDimension[0];

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
    D3DCheckSuccess(device->CreateTexture1D(&textureDesc, &subresourceData, &mTextureObj));
}

void
PlatformTexture1d::CreateShaderResourceView(ID3D11Device4 *device)
{
    D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
    shaderResourceViewDesc.Format = Direct3DTextureFormat[int(mTexturePtr->mFormat)];
    shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE1D;

    // TODO(Wuxiang): Add mipmap support.
    shaderResourceViewDesc.Texture1D.MipLevels = 1;
    shaderResourceViewDesc.Texture1D.MostDetailedMip = 1;
    D3DCheckSuccess(device->CreateShaderResourceView(mTextureObj, &shaderResourceViewDesc, &mShaderResourceView));
}

void
PlatformTexture1d::CreateRenderTargetView(ID3D11Device4 *device)
{
    D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
    renderTargetViewDesc.Format = Direct3DTextureFormat[int(mTexturePtr->mFormat)];
    renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE1D;

    // TODO(Wuxiang): Add mipmap support.
    renderTargetViewDesc.Texture1D.MipSlice = 0;
    D3DCheckSuccess(device->CreateRenderTargetView(mTextureObj, &renderTargetViewDesc, &mRenderTargetView));
}

}

#endif