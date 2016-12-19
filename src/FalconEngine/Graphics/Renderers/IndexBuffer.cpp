#include <FalconEngine/Graphics/Renderers/IndexBuffer.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
IndexBuffer::IndexBuffer(int indexNum, size_t indexChannelByte, BufferUsage usage) :

    // The index buffer doesn't need the vertex array information about index
    // channel dimension. So we pass 1 here.
    Buffer(indexNum, 1, indexChannelByte, usage),
    m_offset(0)
{
}

IndexBuffer::~IndexBuffer()
{
}

}
