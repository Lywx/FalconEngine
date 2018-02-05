#pragma once

#include <FalconEngine/Core/Macro.h>

#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/IndexBuffer.h>

namespace FalconEngine
{

class FALCON_ENGINE_API ModelAccessOption
{
public:
    ModelAccessOption() = default;

public:
    ResourceCreationAccessUsage mPositionUsage = ResourceCreationAccessUsage::Static;
    ResourceCreationAccessUsage mNormalUsage   = ResourceCreationAccessUsage::Static;
    ResourceCreationAccessUsage mTexCoordUsage = ResourceCreationAccessUsage::Static;

    ResourceCreationAccessMode  mPositionMode = ResourceCreationAccessMode::GpuRead;
    ResourceCreationAccessMode  mNormalMode   = ResourceCreationAccessMode::GpuRead;
    ResourceCreationAccessMode  mTexCoordMode = ResourceCreationAccessMode::GpuRead;
};

class FALCON_ENGINE_API ModelLayoutOption
{
public:
    ModelLayoutOption() = default;

public:
    const BufferLayout mPosition = BufferLayout::Separated;
    const BufferLayout mNormal = BufferLayout::Separated;
    const BufferLayout mTexCoord = BufferLayout::Separated;
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
                    ModelAccessOption(),
                    ModelLayoutOption(),
                    ResourceCreationAccessMode::GpuRead,
                    ResourceCreationAccessUsage::Static,
                    IndexType::UnsignedInt);
        return sDefault;
    }

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    ModelImportOption(ModelAccessOption vertexBufferAccess,
                      ModelLayoutOption vertexBufferLayout,
                      ResourceCreationAccessMode indexBufferMode,
                      ResourceCreationAccessUsage indexBufferUsage,
                      IndexType indexType);

public:
    ModelAccessOption mVertexBufferAccess;
    ModelLayoutOption mVertexBufferLayout;
    ResourceCreationAccessMode  mIndexBufferAccessMode;
    ResourceCreationAccessUsage mIndexBufferAccessUsage;
    IndexType mIndexType;
};

}
