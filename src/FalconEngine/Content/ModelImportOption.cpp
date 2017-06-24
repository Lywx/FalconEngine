#pragma once

#include <FalconEngine/Content/ModelImportOption.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
ModelImportOption::ModelImportOption(ModelLayoutOption vertexBufferLayout,
                                     ModelUsageOption  vertexBufferUsage,
                                     BufferUsage       indexBufferUsage,
                                     IndexType         indexType) :
    mVertexBufferLayout(vertexBufferLayout),
    mVertexBufferUsage(vertexBufferUsage),
    mIndexBufferUsage(indexBufferUsage),
    mIndexType(indexType)
{
}

}
