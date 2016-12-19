#include <FalconEngine/Graphics/Renderers/Buffer.h>

namespace FalconEngine
{

FALCON_ENGINE_IMPLEMENT_RTTI(Buffer, Object);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Buffer::Buffer() :
    m_data(nullptr),
    m_dataContainer(nullptr),
    m_dataByteNum(0),
    m_elementNum(0),
    m_elementChannel(0),
    m_usage(BufferUsage::None)
{
}

// @Params:
// elementNum - the element number
// elementSize - the element dimension, vec3 as 3, vec2 as 2.
//
Buffer::Buffer(int elementNum, int elementChannel, size_t elementChannelByte, BufferUsage usage) :
    m_data(nullptr),
    m_dataContainer(nullptr),
    m_dataByteNum(elementNum * elementChannel * elementChannelByte),
    m_elementNum(elementNum),
    m_elementChannel(elementChannel),
    m_usage(usage)
{
}

Buffer::~Buffer()
{
    // When the buffer is allocated using container, then de-construct the container.
    if (m_dataContainer != nullptr)
    {
        delete m_dataContainer;
    }

    // When the buffer is allocated using raw array, then delete the array.
    else
    {
        delete[] m_data;
    }
}


}
