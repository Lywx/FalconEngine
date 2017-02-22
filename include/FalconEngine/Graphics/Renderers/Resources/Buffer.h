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
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Buffer(int elementNum, int elementByteNum, BufferUsage usage);
    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;

public:
    virtual ~Buffer();

public:
    void
    SetElementNum(int elementNum)
    {
        mElementNum = elementNum;
    }

public:
    unsigned char *mData;
    int            mDataByteNum;
    int            mElementNum;
    BufferUsage    mUsage;
};

}
