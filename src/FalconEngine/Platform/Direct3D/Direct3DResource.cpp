#include <FalconEngine/Platform/Direct3D/Direct3DResource.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformResource::PlatformResource(Renderer *, const Object *resource) :
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

    // TODO(Wuxiang): Add mipmap support.
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

void
PlatformResource::CreateResourceViewAsTexture1d(ID3D11Device4 *device, D3D11_RESOURCE_DIMENSION dimension, const Texture *texture)
{
    if (texture->mAttachment[int(TextureMode::Color)])
    {
        CreateRenderTargetView(device, dimension);
    }

    if (texture->mAttachment[int(TextureMode::DepthStencil)])
    {
        CreateDepthStencilView(device, dimension);
    }

    if (texture->mAttachment[int(TextureMode::Image)])
    {
        CreateUnorderedAccessView(device, dimension);
    }

    if (texture->mAttachment[int(TextureMode::Texture)])
    {
        CreateShaderResourceView(device, dimension);
    }
}

void
PlatformResource::CreateResourceViewAsTexture2d(ID3D11Device4 *device, D3D11_RESOURCE_DIMENSION dimension, const Texture *texture)
{
    if (texture->mAttachment[int(TextureMode::Color)])
    {
        CreateRenderTargetView(device, dimension);
    }

    if (texture->mAttachment[int(TextureMode::DepthStencil)])
    {
        CreateDepthStencilView(device, dimension);
    }

    if (texture->mAttachment[int(TextureMode::Image)])
    {
        CreateUnorderedAccessView(device, dimension);
    }

    if (texture->mAttachment[int(TextureMode::Texture)])
    {
        CreateShaderResourceView(device, dimension);
    }
}

/************************************************************************/
/* Protected Members                                                    */
/************************************************************************/
void
PlatformResource::CreateResourceView(ID3D11Device4 *device)
{
    D3D11_RESOURCE_DIMENSION dimension;
    mResourceObj->GetType(&dimension);

    // TODO(Wuxiang): Add support for multiple resource view of same type. But
    // remember that unordered access view is not supported for two of those view.
    if (auto buffer = dynamic_cast<const Buffer *>(mResourcePtr))
    {
        auto bufferType = buffer->GetBufferType();
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
        case BufferType::RenderBuffer:
            FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
            break;
        case BufferType::FeedbackBuffer:
            FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
            break;
        default:
            FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
        }
    }
    else if (auto texture = dynamic_cast<const Texture *>(mResourcePtr))
    {
        auto textureType = texture->GetTextureType();
        switch (textureType)
        {
        case TextureType::Texture1d:
            CreateResourceViewAsTexture1d(device, dimension, texture);
            break;
        case TextureType::Texture2d:
            CreateResourceViewAsTexture2d(device, dimension, texture);
            break;
        case TextureType::Texture2dArray:
            FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
            break;
        case TextureType::Texture3d:
            FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
            break;
        case TextureType::TextureCube:
            FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
            break;
        default:
            FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
        }
    }
    else
    {
        FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
    }
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
    viewDesc.Format = Direct3DResourceFormat[int(mFormat)];

    // TODO(Wuxiang): Add read-only support.
    // https://msdn.microsoft.com/en-us/library/windows/desktop/ff476116(v=vs.85).aspx
    viewDesc.Flags = 0;

    switch (texture->GetTextureType())
    {
    case TextureType::Texture1d:
    {
        viewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE1D;

        // TODO(Wuxiang): Add mipmap support.
        viewDesc.Texture1D.MipSlice = 1;
    }
    break;

    case TextureType::Texture2d:
    {
        viewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

        // TODO(Wuxiang): Add mipmap support.
        viewDesc.Texture2D.MipSlice = 1;
    }
    break;

    case TextureType::Texture2dArray:
    {
        FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();

        // TODO(Wuxiang): Add texture 2d array support.
        // viewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DARRAY;
        // viewDesc.Texture2DArray.ArraySize;
        // viewDesc.Texture2DArray.FirstArraySlice;
        // viewDesc.Texture2DArray.MipSlice;
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
    viewDesc.Format = Direct3DResourceFormat[int(mFormat)];

    switch (mTexturePtr->mType)
    {
    case TextureType::None:
        FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();

    case TextureType::Texture1d:
    {
        viewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE1D;

        // TODO(Wuxiang): Add mipmap support.
        viewDesc.Texture1D.MipLevels = 1;
        viewDesc.Texture1D.MostDetailedMip = 1;
    }
    break;

    case TextureType::Texture2d:
    {
        viewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;

        // TODO(Wuxiang): Add mipmap support.
        viewDesc.Texture2D.MipLevels = 1;
        viewDesc.Texture2D.MostDetailedMip = 1;
    }
    break;

    case TextureType::Texture2dArray:
    {
        FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
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

    switch (mTexturePtr->mType)
    {
    case TextureType::None:
        FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();

    case TextureType::Texture1d:
    {
        viewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE1D;

        // TODO(Wuxiang): Add mipmap support.
        viewDesc.Texture1D.MipSlice = 0;
    }
    break;

    case TextureType::Texture2d:
    {
        viewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

        // TODO(Wuxiang): Add mipmap support.
        viewDesc.Texture2D.MipSlice = 0;
    }
    break;

    case TextureType::Texture2dArray:
    {
        FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
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
        device->CreateRenderTargetView(
            mResourceObj,
            &viewDesc,
            &mRenderTargetView));
}

void
PlatformResource::CreateUnorderedAccessView(ID3D11Device4 *device, D3D11_RESOURCE_DIMENSION dimension)
{
    FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
}

}

#endif