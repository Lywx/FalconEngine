#pragma once

#include <FalconEngine/Graphics/Common.h>
#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>

namespace FalconEngine
{

// @summary A wrapper around buffer that provide various convenient function.
#pragma warning(disable: 4251)
class FALCON_ENGINE_API BufferAdaptor
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit BufferAdaptor(const std::shared_ptr<Buffer>& buffer);
    virtual ~BufferAdaptor();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    template<typename T>
    void
    Fill(const T& value)
    {
        Fill(mBuffer->GetData(), value);
    }

    // @remark Can be used to fill mapped buffer data in pinned memory and keep
    // track of offset at the same time.
    template<typename T>
    void
    Fill(unsigned char *data, const T& value)
    {
        BufferData::Fill<T>(data, mBufferDataRelativeOffsetEnd, value);
    }

    template<typename T, typename S>
    void
    FillAs(const T& value)
    {
        FillAs<T, S>(mBuffer->GetData(), value);
    }

    // @remark Can be used to fill mapped buffer data in pinned memory and keep
    // track of offset at the same time.
    template<typename T, typename S>
    void
    FillAs(unsigned char *data, const T& value)
    {
        BufferData::FillAs<T, S>(data, mBufferDataRelativeOffsetEnd, value);
    }

    virtual void
    FillBegin();

    virtual void
    FillEnd();

    const Buffer *
    GetBuffer() const;

    std::shared_ptr<Buffer>
    GetBuffer();

protected:
    std::shared_ptr<Buffer> mBuffer;

    // A offset marker related to the offset position (so that 'offset' + 'relative
    // offset end' = 'offset end') indicates where the lately filled data is
    // current at in the buffer.
    size_t                  mBufferDataRelativeOffsetEnd;
};
#pragma warning(default: 4251)

}