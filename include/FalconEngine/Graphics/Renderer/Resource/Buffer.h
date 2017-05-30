#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <FalconEngine/Math/Matrix4.h>
#include <FalconEngine/Math/Vector3.h>
#include <FalconEngine/Math/Vector4.h>

namespace FalconEngine
{

enum class FALCON_ENGINE_API BufferAccessMode
{
    None,

    Read,
    ReadWrite,
    Write,

    Count
};

enum class FALCON_ENGINE_API BufferStorage
{
    Interleaved,
    Separated,
};

enum class FALCON_ENGINE_API BufferUsage
{
    None,

    Static,
    Stream,
    Dynamic,

    Count
};

class FALCON_ENGINE_API Buffer
{

protected:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Buffer(int elementNum, size_t elementByteNum, BufferUsage usage);
    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;

public:
    virtual ~Buffer();

public:
    size_t
    GetCapacityByteNum() const;

    unsigned char *
    GetData();

    const unsigned char *
    GetData() const;

    size_t
    GetDataByteNum() const;

    int
    GetElementNum() const;

    void
    SetElementNum(int elementNum);

    BufferUsage
    GetUsage() const;

private:
    unsigned char *mData;

    size_t         mCapacityByteNum;     // Maximum capacity size in bytes include space not used.
    int            mCapacityElementNum;  // Maximum capacity size in term of element number include space not used.

    size_t         mDataByteNum;         // Actual data size in bytes.
    int            mElementNum;          // Actual data size in term of element number.
    size_t         mElementByteNum;      // Each element's data size in bytes.

    BufferUsage    mUsage;
};

// @summary Prevent template parameter deduction because the buffer data filling
// is often where mistakes are made, you better be careful.
//
// @ref http://stackoverflow.com/questions/41634538/prevent-implicit-template-instantiation
template <typename T>
struct Nondeductible
{
    using Type = T;
};

template<typename T>
inline void
FillBufferData(T *data, size_t& dataIndex, T value)
{
    // NOTE(Wuxiang): Notice that the data indexing is based on the T. So if
    // you use int or float at the same time, the indexing would work differently.
    // That usually won't cause problems, if you use reinterpret_cast properly.
    data[dataIndex] = value;
    ++dataIndex;
}

// @param T is the data pointer type you need to fill in.
// @param V is the data type you provide to fill with.
template<typename T, typename V>
inline void
FillBufferDataAs(typename Nondeductible<T>::Type *data, size_t& dataIndex, V value)
{
    FillBufferData<T>(data, dataIndex, T(value));
}

template<typename T>
inline void
FillBufferDataAsVector3f(typename Nondeductible<T>::Type *data, size_t& dataIndex, Vector3f value)
{
    FillBufferDataAs<T, float>(data, dataIndex, value.x);
    FillBufferDataAs<T, float>(data, dataIndex, value.y);
    FillBufferDataAs<T, float>(data, dataIndex, value.z);
}

template<typename T>
inline void
FillBufferDataAsVector4f(typename Nondeductible<T>::Type *data, size_t& dataIndex, Vector4f value)
{
    FillBufferDataAs<T, float>(data, dataIndex, value.x);
    FillBufferDataAs<T, float>(data, dataIndex, value.y);
    FillBufferDataAs<T, float>(data, dataIndex, value.z);
    FillBufferDataAs<T, float>(data, dataIndex, value.w);
}

template<typename T>
inline void
FillBufferDataAsMatrix4f(typename Nondeductible<T>::Type *data, size_t& dataIndex, Matrix4f value)
{
    for (auto i = 0; i < 4; ++i)
    {
        FillBufferDataAsVector4f<T>(data, dataIndex, value[i]);
    }
}

}
