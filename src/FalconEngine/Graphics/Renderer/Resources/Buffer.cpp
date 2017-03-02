#include <FalconEngine/Graphics/Renderer/Resources/Buffer.h>

namespace FalconEngine
{
/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
// @param elementNum - the element number
// @param elementByteNum - the element size in total.
Buffer::Buffer(size_t elementNum, size_t elementByteNum, BufferUsage usage) :
    mElementByteNum(elementByteNum),
    mUsage(usage)
{
    // NOTE(Wuxiang): The capacity is fixed currently.
    mCapacityByteNum = elementNum * elementByteNum;
    mCapacityElementNum = elementNum;

    // NOTE(Wuxiang): The capacity is initially determined by allocation at construction.
    mDataByteNum = mCapacityByteNum;
    mElementNum = mCapacityElementNum;

    mData = new unsigned char[mDataByteNum];
}

Buffer::~Buffer()
{
    delete [] mData;
}


}
