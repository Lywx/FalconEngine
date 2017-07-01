#pragma once

#include <FalconEngine/Graphics/Common.h>

#include <memory>
#include <vector>

#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>

namespace FalconEngine
{

class FALCON_ENGINE_API VertexBuffer : public Buffer
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    VertexBuffer(int vertexNum, size_t vertexByteNum, BufferStorageMode storageMode, BufferUsage usage);
    virtual ~VertexBuffer();
};

}
