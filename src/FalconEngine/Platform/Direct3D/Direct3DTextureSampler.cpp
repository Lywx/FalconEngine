#include <FalconEngine/Platform/Direct3D/Direct3DTextureSampler.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Graphics/Renderer/Renderer.h>
#include <FalconEngine/Platform/Direct3D/Direct3DMapping.h>
#include <FalconEngine/Platform/Direct3D/Direct3DRendererData.h>
#include <FalconEngine/Platform/Win32/Win32Exception.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformSampler::PlatformSampler(Renderer *renderer, const Sampler *sampler) :
    mSampler(sampler),
    mSampleState(nullptr)
{
    Create(renderer->mData->GetDevice());
}

PlatformSampler::~PlatformSampler()
{
    mSampleState->Release();
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformSampler::Enable(Renderer *renderer, int textureUnit, unsigned int shaderMask)
{
    auto context = renderer->mData->GetContext();

    if (GetShaderEnabled(shaderMask, ShaderType::VertexShader))
    {
        context->VSSetSamplers(textureUnit, 1, &mSampleState);
    }

    if (GetShaderEnabled(shaderMask, ShaderType::TessellationControlShader))
    {
        context->HSSetSamplers(textureUnit, 1, &mSampleState);
    }

    if (GetShaderEnabled(shaderMask, ShaderType::TessellationEvaluationShader))
    {
        context->DSSetSamplers(textureUnit, 1, &mSampleState);
    }

    if (GetShaderEnabled(shaderMask, ShaderType::GeometryShader))
    {
        context->GSSetSamplers(textureUnit, 1, &mSampleState);
    }

    if (GetShaderEnabled(shaderMask, ShaderType::FragmentShader))
    {
        context->PSSetSamplers(textureUnit, 1, &mSampleState);
    }

    if (GetShaderEnabled(shaderMask, ShaderType::ComputeShader))
    {
        context->CSSetSamplers(textureUnit, 1, &mSampleState);
    }
}

void
PlatformSampler::Disable(Renderer *renderer, int textureUnit, unsigned int shaderMask)
{
    auto context = renderer->mData->GetContext();

    if (GetShaderEnabled(shaderMask, ShaderType::VertexShader))
    {
        context->VSSetSamplers(textureUnit, 1, nullptr);
    }

    if (GetShaderEnabled(shaderMask, ShaderType::TessellationControlShader))
    {
        context->HSSetSamplers(textureUnit, 1, nullptr);
    }

    if (GetShaderEnabled(shaderMask, ShaderType::TessellationEvaluationShader))
    {
        context->DSSetSamplers(textureUnit, 1, nullptr);
    }

    if (GetShaderEnabled(shaderMask, ShaderType::GeometryShader))
    {
        context->GSSetSamplers(textureUnit, 1, nullptr);
    }

    if (GetShaderEnabled(shaderMask, ShaderType::FragmentShader))
    {
        context->PSSetSamplers(textureUnit, 1, nullptr);
    }

    if (GetShaderEnabled(shaderMask, ShaderType::ComputeShader))
    {
        context->CSSetSamplers(textureUnit, 1, nullptr);
    }
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
void
PlatformSampler::Create(ID3D11Device4 *device)
{
    D3D11_SAMPLER_DESC samplerDesc;

    auto magFilter = mSampler->mMagnificationFilter;
    auto minFilter = mSampler->mMinificationFilter;
    auto mipmapFilter = mSampler->mMipmapFilter;

    // https://msdn.microsoft.com/en-us/library/windows/desktop/ff476132(v=vs.85).aspx
    int filter = 0;
    if (minFilter == SamplerMinificationFilter::Linear)
    {
        filter += 1 << 2;
    }
    if (magFilter == SamplerMagnificationFilter::Linear)
    {
        filter += 1 << 1;
    }
    if (mipmapFilter == SamplerMipmapFilter::Linear)
    {
        filter += 1;
    }

    // NOTE(Wuxiang): In Direct3D you cannot disable mipmapping in sampler state,
    // so mSampler->mMipmapEnabled is not used.
    samplerDesc.Filter = D3D11_FILTER(filter);

    // https://msdn.microsoft.com/en-us/library/windows/desktop/ff476256(v=vs.85).aspx
    samplerDesc.AddressU = Direct3DSamplerWrapMode[int(mSampler->mWrapS)];
    samplerDesc.AddressV = Direct3DSamplerWrapMode[int(mSampler->mWrapT)];
    samplerDesc.AddressW = Direct3DSamplerWrapMode[int(mSampler->mWrapR)];

    // TODO(Wuxiang): Add mipmap support.
    samplerDesc.MipLODBias = 0.0f;

    // TODO(Wuxiang): Add Anisotropy Filtering support.
    samplerDesc.MaxAnisotropy = 1;
    samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;

    // TODO(Wuxiang): Add border color support.
    samplerDesc.BorderColor[0] = 0;
    samplerDesc.BorderColor[1] = 0;
    samplerDesc.BorderColor[2] = 0;
    samplerDesc.BorderColor[3] = 0;

    // TODO(Wuxiang): Add LOD support.
    samplerDesc.MinLOD = 0;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

    // Create the texture sampler state.
    auto result = device->CreateSamplerState(&samplerDesc, &mSampleState);
    D3DCheckSuccess(result);
}

}

#endif