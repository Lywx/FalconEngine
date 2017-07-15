#pragma once

#include <FalconEngine/Graphics/Common.h>

#include <tuple>

#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/BufferAdaptor.h>

namespace FalconEngine
{

class BufferControllerChannel
{
public:
    BufferControllerChannel(std::shared_ptr<BufferAdaptor> adaptor,
                            std::shared_ptr<Buffer>        buffer) :
        mAdaptor(adaptor),
        mBuffer(buffer)
    {
    }

public:
    std::shared_ptr<BufferAdaptor> mAdaptor;
    std::shared_ptr<Buffer>        mBuffer;
};

class FALCON_ENGINE_API BufferController
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    BufferController();
    virtual ~BufferController();

public:
    void
    CreateChannel(int                            channel,
                  std::shared_ptr<BufferAdaptor> channelAdaptor)
    {
        if (mChannelTable.find(channel) != mChannelTable.end())
        {
            FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("Channel has been used.");
        }

        mChannelTable.emplace(channel,
                              channelAdaptor,
                              channelAdaptor->GetBuffer());
    }

    void
    FillChannel(int channel);

    std::tuple<unsigned char *, std::shared_ptr<BufferAdaptor>>
    MapChannel(int channel);

    void
    UpdateChannel(int channel, int channelElement);

    void
    ResetChannel(int channel);

private:
    std::unordered_map<int, BufferControllerChannel> mChannelTable;
};

}
