#include <FalconEngine/Platform/Direct3D/Direct3DTexture.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)

using namespace std;
using namespace placeholders;

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformTexture::PlatformTexture(Renderer *renderer, const Texture *texture) :
    PlatformResource(renderer, texture),
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

}

#endif