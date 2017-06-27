#pragma once

#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>

namespace FalconEngine
{

// @summary A wrapper around buffer that provide various convenient function.
class FALCON_ENGINE_API BufferAdaptor
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit BufferAdaptor(std::shared_ptr<Buffer> buffer);
    virtual ~BufferAdaptor();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    template<typename T>
    void
    Fill(const T& value)
    {
        Fill(GetData(), mBufferDataOffsetEnd, value);
    }

    // @remark Can be used to fill mapped buffer data in pinned memory and keep
    // track of offset at the same time.
    template<typename T>
    void
    Fill(unsigned char *data, const T& value)
    {
        BufferData::Fill(data, mBufferDataOffsetEnd, value);
    }

    template<typename T, typename S>
    void
    FillAs(const T& value)
    {
        FillAs<T, S>(GetData(), mBufferDataOffsetEnd, value);
    }

    // @remark Can be used to fill mapped buffer data in pinned memory and keep
    // track of offset at the same time.
    template<typename T, typename S>
    void
    FillAs(unsigned char *data, const T& value)
    {
        BufferData::FillAs<T, S>(data, mBufferDataOffsetEnd, value);
    }

    virtual void
    FillBegin() = 0;

    virtual void
    FillEnd() = 0;

    size_t
    GetCapacityByteNum() const;

    const unsigned char *
    GetData() const;

    unsigned char *
    GetData();

    size_t
    GetDataByteNum() const;

protected:
    std::shared_ptr<Buffer> mBuffer;
    size_t                  mBufferDataOffsetNext;
    size_t                  mBufferDataOffsetEnd;
};

}