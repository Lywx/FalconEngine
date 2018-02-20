#include <FalconEngine/Platform/Direct3D/Direct3DVertexFormat.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Core/Exception.h>
#include <FalconEngine/Graphics/Renderer/Renderer.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexFormat.h>
#include <FalconEngine/Graphics/Renderer/Resource/ShaderSource.h>
#include <FalconEngine/Platform/Direct3D/Direct3DMapping.h>
#include <FalconEngine/Platform/Direct3D/Direct3DRendererData.h>
#include <FalconEngine/Platform/Win32/Win32Exception.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformVertexFormat::PlatformVertexFormat(Renderer *renderer, const VertexFormat *vertexFormat) :
    mInputLayout(nullptr),
    mVertexFormat(vertexFormat)
{
    CreateInputLayout(renderer->mData->GetDevice());
}

PlatformVertexFormat::~PlatformVertexFormat()
{
    mInputLayout.Reset();
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformVertexFormat::Enable(Renderer *renderer)
{
    renderer->mData->GetContext()->IASetInputLayout(mInputLayout.Get());
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
PlatformVertexFormat::CreateInputLayout(ID3D11Device4 *device)
{
    std::vector<D3D11_INPUT_ELEMENT_DESC> inputElementList;
    inputElementList.assign(mVertexFormat->GetVertexAttributeNum(), D3D11_INPUT_ELEMENT_DESC());

    int vertexAttribNum = mVertexFormat->GetVertexAttributeNum();
    for (int vertexAttribIndex = 0; vertexAttribIndex < vertexAttribNum; ++vertexAttribIndex)
    {
        auto const& vertexAttrib = mVertexFormat->GetVertexAttribute(vertexAttribIndex);

        inputElementList[vertexAttribIndex].SemanticName = vertexAttrib.mName.c_str();
        inputElementList[vertexAttribIndex].SemanticIndex = vertexAttrib.mLocation;
        inputElementList[vertexAttribIndex].Format = Direct3DShaderAttributeFormat[int(vertexAttrib.mType)];
        inputElementList[vertexAttribIndex].InputSlot = vertexAttrib.mBindingIndex;
        inputElementList[vertexAttribIndex].AlignedByteOffset = vertexAttrib.mStride;
        inputElementList[vertexAttribIndex].InputSlotClass = vertexAttrib.mDivision == 0 ? D3D11_INPUT_PER_VERTEX_DATA : D3D11_INPUT_PER_INSTANCE_DATA;
        inputElementList[vertexAttribIndex].InstanceDataStepRate = vertexAttrib.mDivision;
    }

    // Create the vertex input layout.
    ShaderSource *vertexShader = mVertexFormat->GetVertexShader();
    D3DCheckSuccess(
        device->CreateInputLayout(
            inputElementList.data(),
            inputElementList.size(),
            vertexShader->mSource.data(),
            vertexShader->mSource.size(),
            mInputLayout.ReleaseAndGetAddressOf()));
}

}

#endif