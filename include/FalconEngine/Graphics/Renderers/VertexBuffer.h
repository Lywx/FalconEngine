#pragma once

#include <memory>
#include <vector>

#include <FalconEngine/GraphicsInclude.h>
#include <FalconEngine/Graphics/Renderers/Buffer.h>

namespace FalconEngine
{

class VertexBuffer : public Buffer
{
    FALCON_ENGINE_DECLARE_RTTI;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    VertexBuffer(int vertexNum, int vertexChannel, size_t vertexChannelByte, BufferUsage usage);
    virtual ~VertexBuffer();
};

typedef std::shared_ptr<VertexBuffer> VertexBufferPtr;

}
