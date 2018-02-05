#pragma once

#include <cstdint>

#include <FalconEngine/Core/Macro.h>
#include <FalconEngine/Graphics/Renderer/Resource/Resource.h>

namespace FalconEngine
{

// @summary Indicate buffer storage resides on 1) RAM and VRAM or 2) VRAM only.
enum class BufferStorageMode
{
    None,

    Device, // Buffer resides on VRAM only, accessible by CPU only in pinned memory.
    Host,   // Buffer resides on RAM, explicitly copied to VRAM.

    Count
};

enum class BufferType
{
    None,

    VertexBuffer,
    IndexBuffer,
    ShaderBuffer,
    UniformBuffer,

    Count,
};

enum class BufferLayout
{
    Interleaved,
    Separated,
};

FALCON_ENGINE_CLASS_BEGIN Buffer
{
protected:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Buffer(int elementNum,
           size_t elementSize,
           BufferStorageMode storageMode,
           BufferType type,
           ResourceCreationAccessMode accessMode,
           ResourceCreationAccessUsage accessUsage);
    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;

public:
    virtual ~Buffer();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    size_t
    GetCapacitySize() const;

    unsigned char *
    GetData();

    const unsigned char *
    GetData() const;

    size_t
    GetDataSize() const;

    int64_t
    GetDataOffset() const;

    // @remark The reason this function is virtual is that derived classes like
    // VertexBuffer might re-implement this method to provide a way to
    // synchronize with vertex buffer binding.
    //
    // @remark For GPU with over 16GB, roughly 16,000,000,000 bytes. Any 64-bit
    // integer (unsigned or signed) would be large enough to hold the offset.
    virtual void
    SetDataOffset(int64_t dataOffset);

    int
    GetElementNum() const;

    void
    SetElementNum(int elementNum);

    size_t
    GetElementSize() const;

    // @summary Get the offset in terms of size of element.
    int
    GetElementOffset() const;

    BufferStorageMode
    GetStorageMode() const;

    BufferType
    GetType() const;

    ResourceCreationAccessMode
    GetAccessMode() const;

    ResourceCreationAccessUsage
    GetAccessUsage() const;

private:
    ResourceCreationAccessMode    mAccessMode;
    ResourceCreationAccessUsage   mAccessUsage;

    unsigned char        *mData;
    size_t                mDataSize;            // Actual data size in bytes.
    int64_t               mDataOffset;

    size_t                mCapacitySize;        // Maximum capacity size in bytes include space not used.
    int                   mCapacityElementNum;  // Maximum capacity size in term of element number include space not used.

    int                   mElementNum;          // Actual data size in term of element number.
    size_t                mElementSize;         // Each element's data size in bytes.

    BufferStorageMode     mStorageMode;
    BufferType            mType;
};
FALCON_ENGINE_CLASS_END

// @summary Prevent template parameter deduction because the buffer data filling
// is often where mistakes are made, you better be careful.
//
// @ref http://stackoverflow.com/questions/41634538/prevent-implicit-template-instantiation
namespace
{
template <typename T>
struct Nondeductible
{
    using Type = T;
};
}

class BufferData
{
public:
    template<typename T>
    static void
    Fill(unsigned char *data, size_t& offset, const typename Nondeductible<T>::Type& value)
    {
        // NOTE(Wuxiang): You should not worry about the performance overhead here.
        // https://stackoverflow.com/questions/674982/performance-hit-from-c-style-casts
        auto address = reinterpret_cast<T *>(data + offset);
        address[0] = value;
        offset += sizeof(T);
    }

    template<typename T, typename S>
    static void
    FillAs(unsigned char *data, size_t& offset, const T& value)
    {
        Fill<S>(data, offset, S(value));
    }
};

}
