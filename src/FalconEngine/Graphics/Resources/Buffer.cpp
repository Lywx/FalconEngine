#include <FalconEngine/Graphics/Resources/Buffer.h>

namespace FalconEngine {

FALCON_ENGINE_IMPLEMENT_RTTI(Buffer, Object);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Buffer::Buffer() :
    m_elementNum(0),
    m_elementSize(0),
    m_byteNum(0),
    m_usage(BufferUsage::NONE),
    m_data(nullptr)
{
}

// @param elements: the element number
// @param elementSize: the single element size
//
Buffer::Buffer(int elements, int elementSize, BufferUsage usage) :
    m_elementNum(elements),
    m_elementSize(elementSize),
    m_byteNum(elements * elementSize),
    m_usage(usage),
    m_data(nullptr)
{
}

Buffer::~Buffer()
{
}


}
