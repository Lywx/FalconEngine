#pragma once

#include <FalconEngine/GraphicsInclude.h>

namespace FalconEngine
{

enum class BufferAccessMode
{
    None,

    Read,
    ReadWrite,
    Write,

    Count
};

enum class BufferUsage
{
    None,

    Static,
    Stream,
    Dynamic,

    Count
};

class Buffer
{

protected:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Buffer(int elementNum, size_t elementByteNum, BufferUsage usage);
    Buffer(int elementNum, int elementByteNum, BufferUsage usage);
    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;

public:
    virtual ~Buffer();

public:
    int
    GetCapacityByteNum() const
    {
        return mCapacityByteNum;
    }

    unsigned char *
    GetData()
    {
        return mData;
    }

    const unsigned char *
    GetData() const
    {
        return mData;
    }

    int
    GetDataByteNum() const
    {
        return mDataByteNum;
    }

    int
    GetElementNum() const
    {
        return mElementNum;
    }

    void
    SetElementNum(int elementNum)
    {
        mElementNum = elementNum;
        mDataByteNum = mElementByteNum * mElementNum;
    }

    BufferUsage
    GetUsage() const
    {
        return mUsage;
    }

private:
    unsigned char *mData;

    int            mCapacityByteNum;
    int            mCapacityElementNum;

    int            mDataByteNum;
    int            mElementNum;
    int            mElementByteNum;

    BufferUsage    mUsage;
};

}
