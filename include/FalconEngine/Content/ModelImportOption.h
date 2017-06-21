#pragma once

#include <FalconEngine/Content/Header.h>

#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/IndexBuffer.h>

namespace FalconEngine
{

class FALCON_ENGINE_API ModelAccessOption
{
public:
    ModelAccessOption() = default;

public:
    BufferUsage mPosition = BufferUsage::Static;
    BufferUsage mNormal = BufferUsage::Static;
    BufferUsage mTexCoord = BufferUsage::Static;
};

class FALCON_ENGINE_API ModelMemoryOption
{
public:
    ModelMemoryOption() = default;

public:
    const BufferStorage mPosition = BufferStorage::Separated;
    const BufferStorage mNormal = BufferStorage::Separated;
    const BufferStorage mTexCoord = BufferStorage::Separated;
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
                    ModelMemoryOption(),
                    BufferUsage::Static,
                    IndexType::UnsignedInt);
        return sDefault;
    }

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    ModelImportOption(ModelAccessOption vertexBufferUsage,
                      ModelMemoryOption vertexBufferStorage,
                      BufferUsage indexBufferUsage,
                      IndexType indexType);

public:
    ModelAccessOption mVertexBufferUsage;
    ModelMemoryOption mVertexBufferStorage;
    BufferUsage       mIndexBufferUsage;
    IndexType         mIndexType;
};

}
