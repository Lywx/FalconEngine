#pragma once

#include <FalconEngine/GraphicsInclude.h>

#include <memory>
#include <vector>

#include <FalconEngine/Graphics/Renderers/Resources/Buffer.h>

namespace FalconEngine
{

class VertexBuffer : public Buffer
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    VertexBuffer(int vertexNum, size_t vertexByteNum, BufferUsage usage);
    VertexBuffer(int vertexNum, int vertexByteNum, BufferUsage usage);
    virtual ~VertexBuffer();
};

typedef std::shared_ptr<VertexBuffer> VertexBufferSharedPtr;

}
