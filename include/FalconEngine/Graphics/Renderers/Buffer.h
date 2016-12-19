#pragma once

#include <FalconEngine/Core/Object.h>

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

class Buffer : public Object
{
    FALCON_ENGINE_DECLARE_RTTI;

protected:
    Buffer();
    Buffer(int elementNum, int elementChannel, size_t elementChannelByte, BufferUsage usage);

public:
    virtual ~Buffer();

public:
    char       *m_data;
    void       *m_dataContainer;
    size_t      m_dataByteNum;
    size_t      m_elementNum;
    size_t      m_elementChannel;
    BufferUsage m_usage;
};

}
