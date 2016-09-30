#pragma once

#include <FalconEngine/Core/Objects/Object.h>

namespace FalconEngine {

enum class BufferAccessMode
{
    READ,
    WRITE,
    READ_WRITE,

    ENUM_COUNT
};

enum class BufferUsage
{
    NONE, // This value will generate an invalid enum

    STATIC,
    DYNAMIC,

    ENUM_COUNT
};

class Buffer : public Object
{
    FALCON_ENGINE_DECLARE_RTTI;

protected:
    Buffer();
    Buffer(int elements, int elementSize, BufferUsage usage);

public:
    virtual ~Buffer();

    inline int GetElementNum() const;
    inline int GetElementSize() const;

    // An application might want to vary the active number of indices. Use
    // this function to do so. It does not change the data storage, only the
    // Buffer::m_elementNum member. The caller is responsible for saving the
    // original number of indices and resetting this when finished with the
    // index buffer. The caller also should not pass in a number of indices
    // that is larger than the original number of indices.
    inline void SetElementNum(int numElements);

    inline BufferUsage GetUsage() const;

    inline int GetByteNum() const;

    // Manage a copy of the buffer in system memory. Queries of the system
    // memory occur in IndexBuffer and VertexBuffer.
    inline virtual char *GetData() const;

protected:

    int m_elementNum;
    int m_elementSize;
    int m_byteNum;

    BufferUsage m_usage;
    char       *m_data;
};

#include "Buffer.inl"

}