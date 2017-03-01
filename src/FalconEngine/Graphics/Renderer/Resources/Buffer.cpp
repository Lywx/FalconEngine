#include <FalconEngine/Graphics/Renderer/Resources/Buffer.h>

namespace FalconEngine
{
/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Buffer::Buffer(int elementNum, size_t elementByteNum, BufferUsage usage)
    : Buffer(elementNum, int(elementByteNum), usage)
{
}

// @param elementNum - the element number
// @param elementByteNum - the element size in total.
Buffer::Buffer(int elementNum, int elementByteNum, BufferUsage usage) :
    mDataByteNum(elementNum * elementByteNum),
    mElementNum(elementNum),
    mUsage(usage)
{
    mData = new unsigned char[mDataByteNum];
}

Buffer::~Buffer()
{
    delete [] mData;
}


}
