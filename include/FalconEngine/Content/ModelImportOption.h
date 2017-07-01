#pragma once

#include <FalconEngine/Content/Common.h>

#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/IndexBuffer.h>

namespace FalconEngine
{

class FALCON_ENGINE_API ModelLayoutOption
{
public:
    ModelLayoutOption() = default;

public:
    const BufferLayout mPosition = BufferLayout::Separated;
    const BufferLayout mNormal = BufferLayout::Separated;
    const BufferLayout mTexCoord = BufferLayout::Separated;
};

class FALCON_ENGINE_API ModelUsageOption
{
public:
    ModelUsageOption() = default;

public:
    BufferUsage mPosition = BufferUsage::Static;
    BufferUsage mNormal = BufferUsage::Static;
    BufferUsage mTexCoord = BufferUsage::Static;
};

class FALCON_ENGINE_API ModelImportOption
{
public:
    /************************************************************************/
    /* Static Members                                                       */
    /************************************************************************/
    static ModelImportOption GetDefault()
    {
        static const ModelImportOption sDefault = ModelImportOption(
                    ModelLayoutOption(),
                    ModelUsageOption(),
                    BufferUsage::Static,
                    IndexType::UnsignedInt);
        return sDefault;
    }

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    ModelImportOption(ModelLayoutOption vertexBufferLayout,
                      ModelUsageOption  vertexBufferUsage,
                      BufferUsage       indexBufferUsage,
                      IndexType         indexType);

public:
    ModelLayoutOption mVertexBufferLayout;
    ModelUsageOption  mVertexBufferUsage;
    BufferUsage       mIndexBufferUsage;
    IndexType         mIndexType;
};

}
