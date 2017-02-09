#pragma once

#include <FalconEngine/Graphics/GraphicsInclude.h>

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
    FALCON_ENGINE_RTTI_DECLARE;

protected:
    Buffer();
    Buffer(unsigned char *data, int elementNum, int elementByteNum, BufferUsage usage);

public:
    virtual ~Buffer();

public:
    unsigned char *mData;
    int            mDataByteNum;
    int            mElementNum;
    BufferUsage    mUsage;
};

}
