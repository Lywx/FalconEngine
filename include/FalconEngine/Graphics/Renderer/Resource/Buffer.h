#pragma once

#include <cstdint>
#include <string>

#include <FalconEngine/Core/Macro.h>
#include <FalconEngine/Core/Object.h>
#include <FalconEngine/Graphics/Renderer/Resource/Resource.h>

namespace FalconEngine
{

// @summary Used to dynamically switching code interface. This enum has nothing
// to do with API.
enum class BufferType
{
    None,
//                     OpenGL                     / Direct3D
    VertexBuffer,   // GL_ARRAY_BUFFER              D3D11_BIND_VERTEX_BUFFER
    IndexBuffer,    // GL_ELEMENT_ARRAY_BUFFER      D3D11_BIND_INDEX_BUFFER
    ShaderBuffer,   // GL_SHADER_STORAGE_BUFFER     D3D11_BIND_SHADER_RESOURCE, D3D11_BIND_UNORDERED_ACCESS
    UniformBuffer,  // GL_UNIFORM_BUFFER            D3D11_BIND_CONSTANT_BUFFER
    TextureBuffer,  // GL_TEXTURE_BUFFER            D3D11_BIND_SHADER_RESOURCE
    FeedbackBuffer, // GL_TRANSFORM_FEEDBACK_BUFFER D3D11_BIND_STREAM_OUTPUT

    Count,
};

enum class BufferLayout
{
    Interleaved,
    Separated,
};

FALCON_ENGINE_CLASS_BEGIN Buffer :
public Object
{
protected:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Buffer(int elementNum,
           size_t elementSize,
           BufferType type,
           ResourceCreationAccessMode accessMode,
           ResourceCreationAccessUsage accessUsage,
           ResourceStorageMode storageMode);
    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;

public:
    virtual ~Buffer();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    ResourceCreationAccessMode
    GetAccessMode() const;

    ResourceCreationAccessUsage
    GetAccessUsage() const;

    int
    GetBlockIndex() const;

    void
    SetBlockIndex(int blockIndex);

    BufferType
    GetBufferType() const;

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

    const std::string&
    GetName() const;

    ResourceStorageMode
    GetStorageMode() const;

protected:
    ResourceCreationAccessMode mAccessMode;
    ResourceCreationAccessUsage mAccessUsage;

    // NOTE(Wuxiang): Only used in OpenGL for Uniform Block Buffer. The binding
    // point for Uniform Block Buffer.
    int mBindingIndex;

    // NOTE(Wuxiang): Only used in OpenGL for Uniform Block Buffer. The Uniform
    // Block index.
    int mBlockIndex;

    unsigned char *mData;

    // Actual data size in bytes.
    size_t mDataSize;
    int64_t mDataOffset;

    // Maximum capacity size in bytes include space not used.
    size_t mCapacitySize;

    // Maximum capacity size in term of element number include space not used.
    int mCapacityElementNum;

    // Actual data size in term of element number.
    int mElementNum;

    // Each element's data size in bytes.
    size_t mElementSize;

    // Uniform Block name in OpenGL or Constant Buffer name in Direct3D.
    std::string mName;

    ResourceStorageMode mStorageMode;
    BufferType mType;
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
