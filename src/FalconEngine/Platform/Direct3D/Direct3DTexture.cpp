#include <FalconEngine/Platform/Direct3D/Direct3DTexture.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Core/Exception.h>

using namespace std;
using namespace placeholders;

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformTexture::PlatformTexture(Renderer *renderer, const Texture *texture) :
    PlatformResource(renderer, texture),
    mDimension(texture->GetDimension()),
    mMipmapLevel(texture->GetMipmapLevel()),
    mTexturePtr(texture)
{
    mBindFlag = Direct3DResourceBindFlag(mTexturePtr);
    mCpuFlag = Direct3DResourceAccessFlag(mTexturePtr->GetAccessMode());
    mFormat = Direct3DResourceFormat[int(mTexturePtr->GetFormat())];
    mUsage = Direct3DResourceAccessUsage[int(mTexturePtr->GetAccessMode())];
}

PlatformTexture::~PlatformTexture()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformTexture::Enable(Renderer *renderer,
                        int textureUnit,
                        const TextureShaderMaskList& textureShaderMaskList)
{
    ID3D11DeviceContext4 *context = renderer->mData->GetContext();

    // SRV.
    if (GetShaderEnabled(textureShaderMaskList[int(TextureMode::Texture)],
                         ShaderType::VertexShader))
    {
        context->VSSetShaderResources(textureUnit, 1, &mShaderResourceView);
    }

    if (GetShaderEnabled(textureShaderMaskList[int(TextureMode::Texture)],
                         ShaderType::TessellationControlShader))
    {
        context->HSSetShaderResources(textureUnit, 1, &mShaderResourceView);
    }

    if (GetShaderEnabled(textureShaderMaskList[int(TextureMode::Texture)],
                         ShaderType::TessellationEvaluationShader))
    {
        context->DSSetShaderResources(textureUnit, 1, &mShaderResourceView);
    }

    if (GetShaderEnabled(textureShaderMaskList[int(TextureMode::Texture)],
                         ShaderType::GeometryShader))
    {
        context->GSSetShaderResources(textureUnit, 1, &mShaderResourceView);
    }

    if (GetShaderEnabled(textureShaderMaskList[int(TextureMode::Texture)],
                         ShaderType::FragmentShader))
    {
        context->PSSetShaderResources(textureUnit, 1, &mShaderResourceView);
    }

    if (GetShaderEnabled(textureShaderMaskList[int(TextureMode::Texture)],
                         ShaderType::ComputeShader))
    {
        context->CSSetShaderResources(textureUnit, 1, &mShaderResourceView);
    }

    // UAV.
    if (GetShaderEnabled(textureShaderMaskList[int(TextureMode::Image)],
                         ShaderType::ComputeShader))
    {
        // NEW(Wuxiang): Add Append / Consume Buffer counter support.
        context->CSSetUnorderedAccessViews(textureUnit, 1, &mUnorderedAccessView, nullptr);
    }

    // NOTE(Wuxiang): Since the D3D11 UAV can be bound to output merger stage
    // and compute shader stage and the output merger stage require all UAVs,
    // DSVs, RTVs bound in a single call. You can only bind to computer shader
    // here.
}

void
PlatformTexture::Disable(Renderer *renderer,
                         int textureUnit,
                         const TextureShaderMaskList& textureShaderMaskList)
{
    ID3D11DeviceContext4 *context = renderer->mData->GetContext();

    // SRV.
    if (GetShaderEnabled(textureShaderMaskList[int(TextureMode::Texture)],
                         ShaderType::VertexShader))
    {
        context->VSSetShaderResources(textureUnit, 1, nullptr);
    }

    if (GetShaderEnabled(textureShaderMaskList[int(TextureMode::Texture)],
                         ShaderType::TessellationControlShader))
    {
        context->HSSetShaderResources(textureUnit, 1, nullptr);
    }

    if (GetShaderEnabled(textureShaderMaskList[int(TextureMode::Texture)],
                         ShaderType::TessellationEvaluationShader))
    {
        context->DSSetShaderResources(textureUnit, 1, nullptr);
    }

    if (GetShaderEnabled(textureShaderMaskList[int(TextureMode::Texture)],
                         ShaderType::GeometryShader))
    {
        context->GSSetShaderResources(textureUnit, 1, nullptr);
    }

    if (GetShaderEnabled(textureShaderMaskList[int(TextureMode::Texture)],
                         ShaderType::FragmentShader))
    {
        context->PSSetShaderResources(textureUnit, 1, nullptr);
    }

    if (GetShaderEnabled(textureShaderMaskList[int(TextureMode::Texture)],
                         ShaderType::ComputeShader))
    {
        context->CSSetShaderResources(textureUnit, 1, nullptr);
    }

    // UAV.
    if (GetShaderEnabled(textureShaderMaskList[int(TextureMode::Image)],
                         ShaderType::ComputeShader))
    {
        // NEW(Wuxiang): Add Append / Consume Buffer counter support.
        context->CSSetUnorderedAccessViews(textureUnit, 1, nullptr, nullptr);
    }
}

void *
PlatformTexture::Map(Renderer *renderer,
                     int textureIndex,
                     ResourceMapAccessMode access,
                     ResourceMapFlushMode flush,
                     ResourceMapSyncMode sync,
                     int64_t offset,
                     int64_t size)
{
    FALCON_ENGINE_CHECK_NULLPTR(mResourceObj);

    FALCON_ENGINE_UNUSE(flush);
    FALCON_ENGINE_UNUSE(sync);
    FALCON_ENGINE_UNUSE(size);

    D3D11_MAPPED_SUBRESOURCE mappedSubresource;

    // https://msdn.microsoft.com/en-us/library/windows/desktop/ff476183(v=vs.85).aspx
    UINT mapFlags = 0;
    D3DCheckSuccess(renderer->mData->GetContext()->Map(
                        mResourceObj,
                        // NEW(Wuxiang): Add mipmap mapping support.
                        GetSubresourceIndex(0, textureIndex),
                        Direct3DResourceMapMode[int(access)],
                        mapFlags,
                        &mappedSubresource));
    auto data = reinterpret_cast<unsigned char *>(mappedSubresource.pData);
    return data + offset;
}

void
PlatformTexture::Unmap(Renderer *renderer,
                       int textureIndex)
{
    FALCON_ENGINE_CHECK_NULLPTR(mResourceObj);

    renderer->mData->GetContext()->Unmap(mResourceObj, GetSubresourceIndex(0, textureIndex));
}

/************************************************************************/
/* Protected Members                                                    */
/************************************************************************/
int
PlatformTexture::GetSubresourceIndex(int mipmapIndex, int mipmapLevel, int textureIndex)
{
    // NEW(Wuxiang): Add mipmap mapping support.
    return (mipmapLevel + 1) * textureIndex + mipmapIndex;
}

int
PlatformTexture::GetSubresourceIndex(int mipmapIndex, int textureIndex)
{
    return GetSubresourceIndex(mipmapIndex, mMipmapLevel, textureIndex);
}

}

#endif
