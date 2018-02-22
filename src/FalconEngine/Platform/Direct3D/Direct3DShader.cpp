#include <FalconEngine/Platform/Direct3D/Direct3DShader.h>
#include "FalconEngine/Platform/Direct3D/Direct3DBuffer.h"

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Core/Exception.h>
#include <FalconEngine/Graphics/Renderer/Renderer.h>
#include <FalconEngine/Graphics/Renderer/Resource/ShaderSource.h>
#include <FalconEngine/Platform/Direct3D/Direct3DRendererData.h>

using namespace Microsoft::WRL;

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformShader::PlatformShader(Renderer *renderer, Shader *shader) :
    mShaderNum(),
    mShaders()
{
    std::fill_n(mShaders, int(ShaderType::Count), nullptr);

    ID3D11Device4 *device = renderer->mData->GetDevice();

    for (auto shaderIter = shader->GetShaderSourceBegin(); shaderIter != shader->GetShaderSourceEnd(); ++shaderIter)
    {
        auto shaderIndex = shaderIter->first;
        auto shaderType = ShaderTypeMap.at(shaderIndex);
        auto shaderSource = shaderIter->second.get();

        // Compile for each part of shader
        CreateShaderFromString(device, shaderIndex, shaderType, shaderSource->mSource);
    }
}

PlatformShader::~PlatformShader()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformShader::Enable(Renderer *renderer) const
{
    ID3D11DeviceContext4 *context = renderer->mData->GetContext();

    if (mShaders[VertexShaderIndex])
    {
        ComPtr<ID3D11VertexShader> shader;
        mShaders[VertexShaderIndex].As<ID3D11VertexShader>(&shader);
        context->VSSetShader(shader.Get(), nullptr, 0);
    }

    if (mShaders[TessellationControlShaderIndex])
    {
        ComPtr<ID3D11HullShader> shader;
        mShaders[TessellationControlShaderIndex].As<ID3D11HullShader>(&shader);
        context->HSSetShader(shader.Get(), nullptr, 0);
    }

    if (mShaders[TessellationEvaluationShaderIndex])
    {
        ComPtr<ID3D11DomainShader> shader;
        mShaders[TessellationEvaluationShaderIndex].As<ID3D11DomainShader>(&shader);
        context->DSSetShader(shader.Get(), nullptr, 0);
    }

    if (mShaders[GeometryShaderIndex])
    {
        ComPtr<ID3D11GeometryShader> shader;
        mShaders[GeometryShaderIndex].As<ID3D11GeometryShader>(&shader);
        context->GSSetShader(shader.Get(), nullptr, 0);
    }

    if (mShaders[FragmentShaderIndex])
    {
        ComPtr<ID3D11PixelShader> shader;
        mShaders[FragmentShaderIndex].As<ID3D11PixelShader>(&shader);
        context->PSSetShader(shader.Get(), nullptr, 0);
    }

    if (mShaders[ComputeShaderIndex])
    {
        ComPtr<ID3D11ComputeShader> shader;
        mShaders[ComputeShaderIndex].As<ID3D11ComputeShader>(&shader);
        context->CSSetShader(shader.Get(), nullptr, 0);
    }
}

void
PlatformShader::Disable(Renderer *renderer) const
{
    ID3D11DeviceContext4 *context = renderer->mData->GetContext();
    context->VSSetShader(nullptr, nullptr, 0);
    context->HSSetShader(nullptr, nullptr, 0);
    context->DSSetShader(nullptr, nullptr, 0);
    context->GSSetShader(nullptr, nullptr, 0);
    context->PSSetShader(nullptr, nullptr, 0);
    context->CSSetShader(nullptr, nullptr, 0);
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
void
PlatformShader::CreateShaderFromString(ID3D11Device4 *device, int shaderIndex, ShaderType shaderType, const std::string& shaderSource)
{
    switch (shaderType)
    {
    case ShaderType::VertexShader:
    {
        ComPtr<ID3D11VertexShader> shader;
        D3DCheckSuccess(device->CreateVertexShader(shaderSource.data(), shaderSource.size(), nullptr, shader.ReleaseAndGetAddressOf()));
        SetShader(shaderIndex, shader);
    }
    break;
    case ShaderType::TessellationControlShader:
    {
        ComPtr<ID3D11HullShader> shader;
        D3DCheckSuccess(device->CreateHullShader(shaderSource.data(), shaderSource.size(), nullptr, shader.ReleaseAndGetAddressOf()));
        SetShader(shaderIndex, shader);
    }
    break;
    case ShaderType::TessellationEvaluationShader:
    {
        ComPtr<ID3D11DomainShader> shader;
        D3DCheckSuccess(device->CreateDomainShader(shaderSource.data(), shaderSource.size(), nullptr, shader.ReleaseAndGetAddressOf()));
        SetShader(shaderIndex, shader);
    }
    break;
    case ShaderType::GeometryShader:
    {
        ComPtr<ID3D11GeometryShader> shader;
        D3DCheckSuccess(device->CreateGeometryShader(shaderSource.data(), shaderSource.size(), nullptr, shader.ReleaseAndGetAddressOf()));
        SetShader(shaderIndex, shader);
    }
    break;
    case ShaderType::FragmentShader:
    {
        ComPtr<ID3D11PixelShader> shader;
        D3DCheckSuccess(device->CreatePixelShader(shaderSource.data(), shaderSource.size(), nullptr, shader.ReleaseAndGetAddressOf()));
        SetShader(shaderIndex, shader);
    }
    break;
    case ShaderType::ComputeShader:
    {
        ComPtr<ID3D11ComputeShader> shader;
        D3DCheckSuccess(device->CreateComputeShader(shaderSource.data(), shaderSource.size(), nullptr, shader.ReleaseAndGetAddressOf()));
        SetShader(shaderIndex, shader);
    }
    break;
    default:
        FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
    }
}

void
PlatformShader::SetShader(int shaderIndex, ComPtr<ID3D11DeviceChild> shader)
{
    mShaders[shaderIndex] = std::move(shader);
    ++mShaderNum;
}

}

#endif