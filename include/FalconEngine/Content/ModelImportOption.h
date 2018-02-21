#pragma once

#include <FalconEngine/Core/Macro.h>

#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/IndexBuffer.h>

namespace FalconEngine
{

FALCON_ENGINE_CLASS_BEGIN ModelAccessOption
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    ModelAccessOption();

public:
    ResourceCreationAccessUsage mPositionUsage;
    ResourceCreationAccessUsage mNormalUsage;
    ResourceCreationAccessUsage mTexCoordUsage;

    ResourceCreationAccessMode mPositionMode;
    ResourceCreationAccessMode mNormalMode;
    ResourceCreationAccessMode mTexCoordMode;
};
FALCON_ENGINE_CLASS_END

FALCON_ENGINE_CLASS_BEGIN ModelLayoutOption
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    ModelLayoutOption();

public:
    BufferLayout mPosition;
    BufferLayout mNormal;
    BufferLayout mTexCoord;
};
FALCON_ENGINE_CLASS_END

class FALCON_ENGINE_API ModelImportOption
{
public:
    /************************************************************************/
    /* Static Members                                                       */
    /************************************************************************/
    static ModelImportOption
    GetDefault();

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    ModelImportOption(ModelAccessOption vertexBufferAccess,
                      ModelLayoutOption vertexBufferLayout,
                      ResourceCreationAccessMode indexBufferAccessMode,
                      ResourceCreationAccessUsage indexBufferAccessUsage,
                      IndexType indexType);

public:
    ModelAccessOption mVertexBufferAccess;
    ModelLayoutOption mVertexBufferLayout;
    ResourceCreationAccessMode  mIndexBufferAccessMode;
    ResourceCreationAccessUsage mIndexBufferAccessUsage;
    IndexType mIndexType;
};

}
