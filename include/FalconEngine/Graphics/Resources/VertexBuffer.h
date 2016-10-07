#pragma once

#include <memory>

#include <FalconEngine/Graphics/Resources/Buffer.h>

namespace FalconEngine {

class VertexBuffer : public Buffer
{
    FALCON_ENGINE_DECLARE_RTTI;

public:
    VertexBuffer(int vertices, int vertexSize,
                 BufferUsage usage = BufferUsage::STATIC);
    virtual ~VertexBuffer();
};

typedef std::shared_ptr<VertexBuffer> VertexBufferPtr;

}
