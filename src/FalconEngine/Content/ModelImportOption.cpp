#pragma once

#include <FalconEngine/Content/ModelImportOption.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
ModelImportOption::ModelImportOption(ModelAccessOption vertexBufferUsage, ModelMemoryOption vertexBufferStorage, BufferUsage indexBufferUsage, IndexType indexType):
    mVertexBufferUsage(vertexBufferUsage),
    mVertexBufferStorage(vertexBufferStorage),
    mIndexBufferUsage(indexBufferUsage),
    mIndexType(indexType)
{
}

}
