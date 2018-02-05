#pragma once

#include <FalconEngine/Content/ModelImportOption.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
ModelImportOption::ModelImportOption(ModelAccessOption vertexBufferAccess,
                                     ModelLayoutOption vertexBufferLayout,
                                     ResourceCreationAccessMode indexBufferMode,
                                     ResourceCreationAccessUsage indexBufferUsage,
                                     IndexType indexType) :
    mVertexBufferAccess(vertexBufferAccess),
    mVertexBufferLayout(vertexBufferLayout),
    mIndexBufferAccessMode(indexBufferMode),
    mIndexBufferAccessUsage(indexBufferUsage),
    mIndexType(indexType)
{
}

}
