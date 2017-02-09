#include <FalconEngine/Graphics/Renderers/Resources/Buffer.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(Buffer, Object);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Buffer::Buffer() :
    mData(nullptr),
    mDataByteNum(0),
    mElementNum(0),
    mUsage(BufferUsage::None)
{
}

// @param elementNum - the element number
// @param elementByteNum - the element size in total.
Buffer::Buffer(unsigned char *data, int elementNum, int elementByteNum, BufferUsage usage) :
    mData(data),
    mDataByteNum(elementNum * elementByteNum),
    mElementNum(elementNum),
    mUsage(usage)
{
}

Buffer::~Buffer()
{
    // When the buffer is allocated using malloc.
    free(mData);
}


}
