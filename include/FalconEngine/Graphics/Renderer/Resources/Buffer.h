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

template<typename T>
inline void
FillBufferData(T *data, size_t& dataIndex, T value)
{
    data[dataIndex] = value;
    ++dataIndex;
}

// @param T is the data pointer type you need to fill in.
// @param V is the data type you provide to fill with.
template<typename T, typename V>
inline void
FillBufferDataAs(T *data, size_t& dataIndex, V value)
{
    FillBufferData<T>(data, dataIndex, T(value));
}

template<typename T>
inline void
FillBufferDataAsVector3f(T *data, size_t& dataIndex, Vector3f value)
{
    FillBufferDataAs<T, float>(data, dataIndex, value.x);
    FillBufferDataAs<T, float>(data, dataIndex, value.y);
    FillBufferDataAs<T, float>(data, dataIndex, value.z);
}

template<typename T>
inline void
FillBufferDataAsVector4f(T *data, size_t& dataIndex, Vector4f value)
{
    FillBufferDataAs<T, float>(data, dataIndex, value.x);
    FillBufferDataAs<T, float>(data, dataIndex, value.y);
    FillBufferDataAs<T, float>(data, dataIndex, value.z);
    FillBufferDataAs<T, float>(data, dataIndex, value.w);
}

template<typename T>
inline void
FillBufferDataAsMatrix4f(T *data, size_t& dataIndex, Matrix4f value)
{
    for (auto i = 0; i < 4; ++i)
    {
        FillBufferDataAsVector4f(data, dataIndex, value[i]);
    }
}

}
