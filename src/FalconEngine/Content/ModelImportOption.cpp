#include <FalconEngine/Content/ModelImportOption.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
ModelAccessOption::ModelAccessOption() :
    mPositionUsage(ResourceCreationAccessUsage::Static),
    mNormalUsage(ResourceCreationAccessUsage::Static),
    mTexCoordUsage(ResourceCreationAccessUsage::Static),
    mPositionMode(ResourceCreationAccessMode::GpuReadCpuWrite),
    mNormalMode(ResourceCreationAccessMode::GpuReadCpuWrite),
    mTexCoordMode(ResourceCreationAccessMode::GpuReadCpuWrite)
{
}

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
ModelLayoutOption::ModelLayoutOption() :
    mPosition(BufferLayout::Separated),
    mNormal(BufferLayout::Separated),
    mTexCoord(BufferLayout::Separated)
{
}

/************************************************************************/
/* Static Members                                                       */
/************************************************************************/
ModelImportOption
ModelImportOption::GetDefault()
{
    auto vertexBufferAccess = ModelAccessOption();
    vertexBufferAccess.mPositionUsage = ResourceCreationAccessUsage::Static;
    vertexBufferAccess.mNormalUsage = ResourceCreationAccessUsage::Static;
    vertexBufferAccess.mTexCoordUsage = ResourceCreationAccessUsage::Static;
    vertexBufferAccess.mPositionMode = ResourceCreationAccessMode::GpuReadCpuWrite;
    vertexBufferAccess.mNormalMode = ResourceCreationAccessMode::GpuReadCpuWrite;
    vertexBufferAccess.mTexCoordMode = ResourceCreationAccessMode::GpuReadCpuWrite;

    auto vertexBufferLayout = ModelLayoutOption();
    vertexBufferLayout.mPosition = BufferLayout::Separated;
    vertexBufferLayout.mNormal = BufferLayout::Separated;
    vertexBufferLayout.mTexCoord = BufferLayout::Separated;

    auto indexBufferAccessMode = ResourceCreationAccessMode::GpuReadCpuWrite;
    auto indexBufferAccessUsage = ResourceCreationAccessUsage::Static;

    static const ModelImportOption sInstance = ModelImportOption(
                vertexBufferAccess,
                vertexBufferLayout,
                indexBufferAccessMode,
                indexBufferAccessUsage,
                IndexType::UnsignedInt);

    return sInstance;
}

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
ModelImportOption::ModelImportOption(ModelAccessOption vertexBufferAccess,
                                     ModelLayoutOption vertexBufferLayout,
                                     ResourceCreationAccessMode indexBufferAccessMode,
                                     ResourceCreationAccessUsage indexBufferAccessUsage,
                                     IndexType indexType) :
    mVertexBufferAccess(vertexBufferAccess),
    mVertexBufferLayout(vertexBufferLayout),
    mIndexBufferAccessMode(indexBufferAccessMode),
    mIndexBufferAccessUsage(indexBufferAccessUsage),
    mIndexType(indexType)
{
}

}
