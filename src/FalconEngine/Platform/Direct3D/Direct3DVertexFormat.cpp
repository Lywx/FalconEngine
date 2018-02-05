#include <FalconEngine/Platform/Direct3D/Direct3DVertexFormat.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Core/Exception.h>
#include <FalconEngine/Graphics/Renderer/Renderer.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexFormat.h>
#include <FalconEngine/Platform/Direct3D/Direct3DMapping.h>
#include <FalconEngine/Platform/Direct3D/Direct3DRendererData.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformVertexFormat::PlatformVertexFormat(Renderer *renderer, const VertexFormat *vertexFormat) :
    mInputLayout(nullptr),
    mVertexFormat(vertexFormat)
{
    Create(renderer->mData->GetDevice());
}

PlatformVertexFormat::~PlatformVertexFormat()
{
    mInputLayout->Release();
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformVertexFormat::Enable(Renderer *renderer)
{
    renderer->mData->GetContext()->IASetInputLayout(mInputLayout);
}


void
PlatformVertexFormat::Disable(Renderer *renderer)
{
    renderer->mData->GetContext()->IASetInputLayout(nullptr);
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
void
PlatformVertexFormat::Create(ID3D11Device4 *device)
{
    auto& vertexAttributeList = mVertexFormat->mVertexAttributeList;

    std::vector<D3D11_INPUT_ELEMENT_DESC> inputElementList;
    inputElementList.assign(vertexAttributeList.size(), D3D11_INPUT_ELEMENT_DESC());

    for (size_t vertexAttribIndex = 0; vertexAttribIndex < vertexAttributeList.size(); ++vertexAttribIndex)
    {
        auto& vertexAttribute = vertexAttributeList[vertexAttribIndex];
        inputElementList[vertexAttribIndex].SemanticName = vertexAttribute.mName.c_str();
        inputElementList[vertexAttribIndex].SemanticIndex = vertexAttribute.mLocation;
        inputElementList[vertexAttribIndex].Format = Direct3DShaderAttributeFormat[int(vertexAttribute.mType)];
        inputElementList[vertexAttribIndex].InputSlot = vertexAttribute.mBindingIndex;
        inputElementList[vertexAttribIndex].AlignedByteOffset = vertexAttribute.mStride;
        inputElementList[vertexAttribIndex].InputSlotClass = vertexAttribute.mDivision == 0 ? D3D11_INPUT_PER_VERTEX_DATA : D3D11_INPUT_PER_INSTANCE_DATA;
        inputElementList[vertexAttribIndex].InstanceDataStepRate = vertexAttribute.mDivision;
    }

    // Create the vertex input layout.
    auto result = device->CreateInputLayout(
                      inputElementList.data(),
                      inputElementList.size(),
                      vertexShaderBuffer->GetBufferPointer(),
                      vertexShaderBuffer->GetBufferSize(),
                      &mInputLayout);

    FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
}

}

#endif