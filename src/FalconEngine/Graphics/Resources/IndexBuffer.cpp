#include <FalconEngine/Graphics/Resources/IndexBuffer.h>

namespace FalconEngine {

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
IndexBuffer::IndexBuffer(int indices, int indexSize, BufferUsage usage)
    : Buffer(indices, indexSize, usage)
    , m_offset(0)
{
}

IndexBuffer::~IndexBuffer()
{
    // TODO
    // Renderer::UnbindAll(this);
}

}
