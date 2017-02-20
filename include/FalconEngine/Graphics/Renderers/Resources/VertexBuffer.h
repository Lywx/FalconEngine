#pragma once

#include <FalconEngine/Graphics/GraphicsInclude.h>

#include <memory>
#include <vector>

#include <FalconEngine/Graphics/Renderers/Resources/Buffer.h>

namespace FalconEngine
{

class VertexBuffer : public Buffer
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    VertexBuffer(int vertexNum, int vertexByteNum, BufferUsage usage);
    virtual ~VertexBuffer();
};

typedef std::shared_ptr<VertexBuffer> VertexBufferSharedPtr;

}
