#include <FalconEngine/Platform/Direct3D/Direct3DTexture.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformTexture::PlatformTexture(Renderer *renderer, const Texture *texture) :
    PlatformResource(renderer),
    mTexturePtr(texture)
{
    mFormat = Direct3DResourceFormat[int(texture->mFormat)];
    mUsage = Direct3DResourceAccessUsage[int(texture->mAccessMode)];
}

PlatformTexture::~PlatformTexture()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformTexture::Enable(Renderer *renderer, int textureUnit)
{
    // TODO(Wuxiang): Support multiple shader stage.
    // TODO(Wuxiang): Support other resource view.
    renderer->mData->GetContext()->PSSetShaderResources(textureUnit, 1, &mShaderResourceView);
}

void
PlatformTexture::Disable(Renderer *renderer, int textureUnit)
{
    // TODO(Wuxiang): Support multiple shader stage.
    // TODO(Wuxiang): Support other resource view.
    renderer->mData->GetContext()->PSSetShaderResources(textureUnit, 1, nullptr);
}

/************************************************************************/
/* Protected Members                                                    */
/************************************************************************/
void
PlatformTexture::CreateShaderResourceView(ID3D11Device4 *device)
{
    FALCON_ENGINE_CHECK_ASSERTION(!mShaderResourceView);
    FALCON_ENGINE_CHECK_NULLPTR(mResourceObj);

    D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
    shaderResourceViewDesc.Format = Direct3DResourceFormat[int(mFormat)];

    switch (mTexturePtr->mType)
    {
    case TextureType::None:
        FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();

    case TextureType::Texture1d:
    {
        shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE1D;

        // TODO(Wuxiang): Add mipmap support.
        shaderResourceViewDesc.Texture1D.MipLevels = 1;
        shaderResourceViewDesc.Texture1D.MostDetailedMip = 1;
    }
    break;

    case TextureType::Texture2d:
    {
        shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;

        // TODO(Wuxiang): Add mipmap support.
        shaderResourceViewDesc.Texture2D.MipLevels = 1;
        shaderResourceViewDesc.Texture2D.MostDetailedMip = 1;
    }
    break;

    case TextureType::Texture2dArray:
    {

    }
    break;

    case TextureType::Texture3d:
    {

    }
    break;

    case TextureType::TextureCube:
    {

    }
    break;

    default:
        FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
    }

    D3DCheckSuccess(
        device->CreateShaderResourceView(
            mResourceObj,
            &shaderResourceViewDesc,
            &mShaderResourceView));
}

void
PlatformTexture::CreateRenderTargetView(ID3D11Device4 *device)
{
    FALCON_ENGINE_CHECK_ASSERTION(!mRenderTargetView);
    FALCON_ENGINE_CHECK_NULLPTR(mResourceObj);

    D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
    renderTargetViewDesc.Format = Direct3DResourceFormat[int(mFormat)];

    switch (mTexturePtr->mType)
    {
    case TextureType::None:
        FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();

    case TextureType::Texture1d:
    {
        renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE1D;

        // TODO(Wuxiang): Add mipmap support.
        renderTargetViewDesc.Texture1D.MipSlice = 0;
    }
    break;

    case TextureType::Texture2d:
    {
        renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

        // TODO(Wuxiang): Add mipmap support.
        renderTargetViewDesc.Texture2D.MipSlice = 0;
    }
    break;

    case TextureType::Texture2dArray:
    {

    }
    break;

    case TextureType::Texture3d:
    {

    }
    break;

    case TextureType::TextureCube:
    {

    }
    break;

    default:
        FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
    }

    D3DCheckSuccess(
        device->CreateRenderTargetView(
            mResourceObj,
            &renderTargetViewDesc,
            &mRenderTargetView));
}
}

#endif