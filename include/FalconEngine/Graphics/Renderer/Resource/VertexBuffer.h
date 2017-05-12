#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <memory>
#include <vector>

#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>

namespace FalconEngine
{

class FALCON_ENGINE_ITEM_GRAPHICS VertexBuffer : public Buffer
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    VertexBuffer(size_t vertexNum, size_t vertexByteNum, BufferUsage usage);
    virtual ~VertexBuffer();
};

typedef std::shared_ptr<VertexBuffer> VertexBufferSharedPtr;

}
