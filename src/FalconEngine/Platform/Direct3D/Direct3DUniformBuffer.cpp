#include <FalconEngine/Platform/Direct3D/Direct3DUniformBuffer.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Graphics/Renderer/Resource/UniformBuffer.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformUniformBuffer::PlatformUniformBuffer(Renderer *renderer, const UniformBuffer *uniformBuffer) :
    PlatformBuffer(renderer, uniformBuffer)
{
}

PlatformUniformBuffer::~PlatformUniformBuffer()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformUniformBuffer::Enable(Renderer *renderer, unsigned int bindingIndex, unsigned int shaderMask)
{
    auto context = renderer->mData->GetContext();

    if (GetShaderEnabled(shaderMask, ShaderType::VertexShader))
    {
        context->VSSetConstantBuffers(bindingIndex, 1, mBufferObj.GetAddressOf());
    }

    if (GetShaderEnabled(shaderMask, ShaderType::TessellationControlShader))
    {
        context->HSSetConstantBuffers(bindingIndex, 1, mBufferObj.GetAddressOf());
    }

    if (GetShaderEnabled(shaderMask, ShaderType::TessellationEvaluationShader))
    {
        context->DSSetConstantBuffers(bindingIndex, 1, mBufferObj.GetAddressOf());
    }

    if (GetShaderEnabled(shaderMask, ShaderType::GeometryShader))
    {
        context->GSSetConstantBuffers(bindingIndex, 1, mBufferObj.GetAddressOf());
    }

    if (GetShaderEnabled(shaderMask, ShaderType::FragmentShader))
    {
        context->PSSetConstantBuffers(bindingIndex, 1, mBufferObj.GetAddressOf());
    }

    if (GetShaderEnabled(shaderMask, ShaderType::ComputeShader))
    {
        context->CSSetConstantBuffers(bindingIndex, 1, mBufferObj.GetAddressOf());
    }
}

void
PlatformUniformBuffer::Disable(Renderer *renderer, unsigned int bindingIndex, unsigned int shaderMask)
{
    auto context = renderer->mData->GetContext();

    if (GetShaderEnabled(shaderMask, ShaderType::VertexShader))
    {
        context->VSSetConstantBuffers(bindingIndex, 1, nullptr);
    }

    if (GetShaderEnabled(shaderMask, ShaderType::TessellationControlShader))
    {
        context->HSSetConstantBuffers(bindingIndex, 1, nullptr);
    }

    if (GetShaderEnabled(shaderMask, ShaderType::TessellationEvaluationShader))
    {
        context->DSSetConstantBuffers(bindingIndex, 1, nullptr);
    }

    if (GetShaderEnabled(shaderMask, ShaderType::GeometryShader))
    {
        context->GSSetConstantBuffers(bindingIndex, 1, nullptr);
    }

    if (GetShaderEnabled(shaderMask, ShaderType::FragmentShader))
    {
        context->PSSetConstantBuffers(bindingIndex, 1, nullptr);
    }

    if (GetShaderEnabled(shaderMask, ShaderType::ComputeShader))
    {
        context->CSSetConstantBuffers(bindingIndex, 1, nullptr);
    }
}

void *
PlatformUniformBuffer::Map(Renderer *renderer)
{
    return PlatformBuffer::Map(renderer,
                               ResourceMapAccessMode::WriteBufferInvalidateBuffer,
                               ResourceMapFlushMode::Automatic,
                               ResourceMapSyncMode::Unsynchronized,
                               0,
                               mBufferPtr->GetCapacitySize());
}

}

#endif