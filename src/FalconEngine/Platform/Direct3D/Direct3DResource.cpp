#include <FalconEngine/Platform/Direct3D/Direct3DResource.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Core/Exception.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformResource::PlatformResource(Renderer *, const Object *resource) :
    mBindFlag(0),
    mCpuFlag(0),
    mFormat(DXGI_FORMAT_UNKNOWN),
    mMiscFlags(0),
    mUsage(D3D11_USAGE_DEFAULT),
    mDepthStencilView(nullptr),
    mRenderTargetView(nullptr),
    mShaderResourceView(nullptr),
    mUnorderedAccessView(nullptr),
    mResourceObj(nullptr),
    mResourcePtr(resource)
{
}

PlatformResource::~PlatformResource()
{
    mResourceObj->Release();

    if (mDepthStencilView)
    {
        mDepthStencilView->Release();
    }

    if (mRenderTargetView)
    {
        mRenderTargetView->Release();
    }

    if (mShaderResourceView)
    {
        mShaderResourceView->Release();
    }

    if (mUnorderedAccessView)
    {
        mUnorderedAccessView->Release();
    }
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void *
PlatformResource::Map(Renderer *renderer, ResourceMapAccessMode access, ResourceMapFlushMode flush,
                      ResourceMapSyncMode sync, int64_t offset, int64_t size)
{
    FALCON_ENGINE_CHECK_NULLPTR(mResourceObj);

    _UNUSED(flush);
    _UNUSED(sync);
    _UNUSED(size);

    D3D11_MAPPED_SUBRESOURCE mappedSubresource;
    D3DCheckSuccess(renderer->mData->GetContext()->Map(
                        mResourceObj,
                        0,
                        Direct3DResourceMapMode[int(access)],
                        0,
                        &mappedSubresource));
    auto data = reinterpret_cast<unsigned char *>(mappedSubresource.pData);
    return data + offset;
}

void
PlatformResource::Unmap(Renderer *renderer)
{
    FALCON_ENGINE_CHECK_NULLPTR(mResourceObj);

    renderer->mData->GetContext()->Unmap(mResourceObj, 0);
}

/************************************************************************/
/* Protected Members                                                    */
/************************************************************************/
D3D11_RESOURCE_DIMENSION
PlatformResource::GetDimension() const
{
    D3D11_RESOURCE_DIMENSION dimension;
    mResourceObj->GetType(&dimension);
    return dimension;
}

void
PlatformResource::CreateDepthStencilView(ID3D11Device4 *device, D3D11_RESOURCE_DIMENSION dimension)
{
    FALCON_ENGINE_CHECK_ASSERTION(!mShaderResourceView);
    FALCON_ENGINE_CHECK_ASSERTION(
        dimension == D3D11_RESOURCE_DIMENSION_TEXTURE1D
        || dimension == D3D11_RESOURCE_DIMENSION_TEXTURE2D);
    FALCON_ENGINE_CHECK_NULLPTR(mResourceObj);
    auto texture = dynamic_cast<const Texture *>(mResourceObj);
    FALCON_ENGINE_CHECK_NULLPTR(texture);

    D3D11_DEPTH_STENCIL_VIEW_DESC viewDesc;
    viewDesc.Format = mFormat;

    // TODO(Wuxiang): Add read-only support.
    // https://msdn.microsoft.com/en-us/library/windows/desktop/ff476116(v=vs.85).aspx
    viewDesc.Flags = 0;

    switch (texture->GetTextureType())
    {
    case TextureType::Texture1d:
    {
        viewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE1D;
        viewDesc.Texture1D.MipSlice = 0;
    }
    break;
    case TextureType::Texture1dArray:
    {
        viewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE1DARRAY;
        viewDesc.Texture1DArray.ArraySize = texture->mDimension[2];
        viewDesc.Texture1DArray.FirstArraySlice = 0;
        viewDesc.Texture1DArray.MipSlice = 0;
    }
    break;
    case TextureType::Texture2d:
    {
        viewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
        viewDesc.Texture2D.MipSlice = 0;
    }
    break;
    case TextureType::Texture2dArray:
    {
        viewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DARRAY;
        viewDesc.Texture2DArray.ArraySize = texture->mDimension[2];
        viewDesc.Texture2DArray.FirstArraySlice = 0;
        viewDesc.Texture2DArray.MipSlice = 0;
    }
    break;
    case TextureType::Texture3d:
    {
        FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
    }
    break;
    case TextureType::TextureCube:
    {
        FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
    }
    break;
    default:
        FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
    }

    D3DCheckSuccess(
        device->CreateDepthStencilView(
            mResourceObj,
            &viewDesc,
            &mDepthStencilView));
}

void
PlatformResource::CreateShaderResourceView(ID3D11Device4 *device, D3D11_RESOURCE_DIMENSION dimension)
{
    FALCON_ENGINE_CHECK_ASSERTION(!mShaderResourceView);
    FALCON_ENGINE_CHECK_NULLPTR(mResourceObj);

    D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc;
    viewDesc.Format = mFormat;

    if (dimension == D3D11_RESOURCE_DIMENSION_BUFFER)
    {
        auto buffer = dynamic_cast<const Buffer *>(mResourceObj);
        FALCON_ENGINE_CHECK_NULLPTR(buffer);

        // NEW(Wuxiang): Add Append / Consume Buffer support.
        // NEW(Wuxiang): Add Buffer / Structured Buffer support.
        // NEW(Wuxiang): Add Byte Address Buffer support.
        FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
    }
    else
    {
        auto texture = dynamic_cast<const Texture *>(mResourceObj);
        FALCON_ENGINE_CHECK_NULLPTR(texture);

        switch (texture->GetTextureType())
        {
        case TextureType::Texture1d:
        {
            viewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE1D;
            viewDesc.Texture1D.MipLevels = texture->mMipmapLevel;
            viewDesc.Texture1D.MostDetailedMip = 0;
        }
        break;
        case TextureType::Texture1dArray:
        {
            viewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE1D;
            viewDesc.Texture1DArray.ArraySize = texture->mDimension[2];
            viewDesc.Texture1DArray.FirstArraySlice = 0;
            viewDesc.Texture1DArray.MipLevels = texture->mMipmapLevel;
            viewDesc.Texture1DArray.MostDetailedMip = 0;
        }
        break;
        case TextureType::Texture2d:
        {
            viewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
            viewDesc.Texture2D.MipLevels = texture->mMipmapLevel;
            viewDesc.Texture2D.MostDetailedMip = 0;
        }
        break;
        case TextureType::Texture2dArray:
        {
            viewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
            viewDesc.Texture2DArray.ArraySize = texture->mDimension[2];
            viewDesc.Texture2DArray.FirstArraySlice = 0;
            viewDesc.Texture2DArray.MipLevels = texture->mMipmapLevel;
            viewDesc.Texture2DArray.MostDetailedMip = 0;
        }
        break;
        case TextureType::Texture3d:
        {
            FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
        }
        break;
        case TextureType::TextureCube:
        {
            FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
        }
        break;
        default:
            FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
        }
    }

    D3DCheckSuccess(
        device->CreateShaderResourceView(
            mResourceObj,
            &viewDesc,
            &mShaderResourceView));
}

void
PlatformResource::CreateRenderTargetView(ID3D11Device4 *device, D3D11_RESOURCE_DIMENSION dimension)
{
    FALCON_ENGINE_CHECK_ASSERTION(!mRenderTargetView);
    FALCON_ENGINE_CHECK_NULLPTR(mResourceObj);

    D3D11_RENDER_TARGET_VIEW_DESC viewDesc;
    viewDesc.Format = Direct3DResourceFormat[int(mFormat)];

    if (dimension == D3D11_RESOURCE_DIMENSION_BUFFER)
    {
        auto buffer = dynamic_cast<const Buffer *>(mResourceObj);
        FALCON_ENGINE_CHECK_NULLPTR(buffer);

        // NEW(Wuxiang): Add Buffer support.
        FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
    }
    else
    {
        auto texture = dynamic_cast<const Texture *>(mResourceObj);
        FALCON_ENGINE_CHECK_NULLPTR(texture);

        switch (texture->GetTextureType())
        {
        case TextureType::Texture1d:
        {
            viewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE1D;
            // NEW(Wuxiang): Add MRT support.
            viewDesc.Texture1D.MipSlice = 0;
        }
        break;
        case TextureType::Texture1dArray:
        {
            viewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE1DARRAY;
            viewDesc.Texture1DArray.ArraySize = texture->mDimension[2];
            viewDesc.Texture1DArray.FirstArraySlice = 0;
            // NEW(Wuxiang): Add MRT support.
            viewDesc.Texture1DArray.MipSlice = 0;
        }
        break;
        case TextureType::Texture2d:
        {
            viewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
            // NEW(Wuxiang): Add MRT support.
            viewDesc.Texture2D.MipSlice = 0;
        }
        break;
        case TextureType::Texture2dArray:
        {
            viewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
            viewDesc.Texture2DArray.ArraySize = texture->mDimension[2];
            viewDesc.Texture2DArray.FirstArraySlice = 0;
            // NEW(Wuxiang): Add MRT support.
            viewDesc.Texture2DArray.MipSlice = 0;
        }
        break;
        case TextureType::Texture3d:
        {
            FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
        }
        break;
        case TextureType::TextureCube:
        {
            FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
        }
        break;
        default:
            FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
        }
    }

    D3DCheckSuccess(
        device->CreateRenderTargetView(
            mResourceObj,
            &viewDesc,
            &mRenderTargetView));
}

void
PlatformResource::CreateUnorderedAccessView(ID3D11Device4 *device, D3D11_RESOURCE_DIMENSION dimension)
{
    _UNUSED(device);
    _UNUSED(dimension);

    FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
}

}

#endif