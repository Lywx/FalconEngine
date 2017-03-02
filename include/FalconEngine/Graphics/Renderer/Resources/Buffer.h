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
    Buffer(size_t elementNum, size_t elementByteNum, BufferUsage usage);
    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;

public:
    virtual ~Buffer();

public:
    size_t
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

    size_t
    GetDataByteNum() const
    {
        return mDataByteNum;
    }

    size_t
    GetElementNum() const
    {
        return mElementNum;
    }

    void
    SetElementNum(size_t elementNum)
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

    size_t         mCapacityByteNum;
    size_t         mCapacityElementNum;

    size_t         mDataByteNum;
    size_t         mElementNum;
    size_t         mElementByteNum;

    BufferUsage    mUsage;
};

}
