#include <FalconEngine/Platform/Direct3D/Direct3DShader.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Core/Exception.h>
#include <FalconEngine/Graphics/Renderer/Renderer.h>
#include <FalconEngine/Graphics/Renderer/Shader/ShaderSource.h>
#include <FalconEngine/Platform/Direct3D/Direct3DRendererData.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformShader::PlatformShader(Renderer *renderer, Shader *shader) :
    mShaderNum(),
    mShaders()
{
    std::fill_n(mShaders, int(ShaderType::Count), 0);

    ID3D11DeviceContext4 *context = renderer->mData->GetContext();
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
    context->CSSetShader();
}

void
PlatformShader::Disable(Renderer *renderer) const
{
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
        ID3D11VertexShader *shader;
        D3DCompile(shaderSource.data(), shaderSource.size(), nullptr, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, )
        device->CreateVertexShader(shaderSource.data(), shaderSource.size(), nullptr, &shader);
        SetShader(shaderIndex, shader);
    }
    break;
    case ShaderType::TessellationControlShader:
    {
        ID3D11HullShader *shader;
        device->CreateHullShader(shaderSource.data(), shaderSource.size(), nullptr, &shader);
        SetShader(shaderIndex, shader);
    }
    break;
    case ShaderType::TessellationEvaluationShader:
    {
        ID3D11DomainShader *shader;
        device->CreateDomainShader(shaderSource.data(), shaderSource.size(), nullptr, &shader);
        SetShader(shaderIndex, shader);
    }
    break;
    case ShaderType::GeometryShader:
    {
        ID3D11GeometryShader *shader;
        device->CreateGeometryShader(shaderSource.data(), shaderSource.size(), nullptr, &shader);
        SetShader(shaderIndex, shader);
    }
    break;
    case ShaderType::FragmentShader:
    {
        ID3D11PixelShader *shader;
        device->CreatePixelShader(shaderSource.data(), shaderSource.size(), nullptr, &shader);
        SetShader(shaderIndex, shader);
    }
    break;
    case ShaderType::ComputeShader:
    {
        ID3D11ComputeShader *shader;
        device->CreateComputeShader(shaderSource.data(), shaderSource.size(), nullptr, &shader);
        SetShader(shaderIndex, shader);
    }
    break;
    default:
        FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
    }
}

void
PlatformShader::SetShader(int shaderIndex, ID3D11DeviceChild *shader)
{
    mShaders[shaderIndex] = shader;
    ++mShaderNum;
}

}

#endif