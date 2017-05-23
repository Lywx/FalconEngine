#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>

namespace FalconEngine
{
/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
// @param elementNum - the element number
// @param elementByteNum - the element size in total.
Buffer::Buffer(int elementNum, size_t elementByteNum, BufferUsage usage) :
    mElementByteNum(elementByteNum),
    mUsage(usage)
{
    assert(elementNum >= 0);

    // NOTE(Wuxiang): The capacity is fixed currently.
    mCapacityByteNum = size_t(elementNum) * elementByteNum;
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

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
unsigned char *
Buffer::GetData()
{
    return mData;
}

const unsigned char *
Buffer::GetData() const
{
    return mData;
}

size_t
Buffer::GetDataByteNum() const
{
    return mDataByteNum;
}

void
Buffer::SetElementNum(int elementNum)
{
    assert(elementNum >= 0);

    mElementNum = elementNum;
    mDataByteNum = size_t(mElementByteNum) * mElementNum;
}

BufferUsage
Buffer::GetUsage() const
{
    return mUsage;
}
}
