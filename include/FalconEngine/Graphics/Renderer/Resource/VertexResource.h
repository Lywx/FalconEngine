#pragma once

#include <FalconEngine/Graphics/Common.h>

#include <tuple>
#include <map>

#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/BufferAdaptor.h>
#include <FalconEngine/Graphics/Renderer/Scene/Visual.h>

namespace FalconEngine
{

class VertexResourceChannel
{
public:
    VertexResourceChannel(const std::shared_ptr<Buffer>&        buffer,
                          const std::shared_ptr<BufferAdaptor>& bufferAdaptor,
                          const std::shared_ptr<Visual>&        visual) :
        mBuffer(buffer),
        mBufferAdaptor(bufferAdaptor),
        mData(nullptr),
        mElementNum(0),
        mVisual(visual)
    {
    }

public:
    std::shared_ptr<Buffer>        mBuffer;
    std::shared_ptr<BufferAdaptor> mBufferAdaptor;
    unsigned char                 *mData;
    int                            mElementNum;
    std::shared_ptr<Visual>        mVisual;
};

class FALCON_ENGINE_API VertexResource
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    VertexResource();
    virtual ~VertexResource();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    CheckChannelValid(int channel) const;

    void
    CreateChannel(int                            channel,
                  std::shared_ptr<BufferAdaptor> channelAdaptor,
                  std::shared_ptr<Visual>        channelVisual);

    std::tuple<BufferAdaptor *, unsigned char *>
    GetChannelData(int channel);

    // @remark Only provide const visual pointer rather than the shared_ptr
    // version for efficient use in rendering.
    const Visual *
    GetChannelVisual(int channel) const;

    void
    MapChannel(BufferAccessMode          access,
               BufferFlushMode           flush,
               BufferSynchronizationMode synchronization);

    void
    MapChannel(int                       channel,
               BufferAccessMode          access,
               BufferFlushMode           flush,
               BufferSynchronizationMode synchronization);

    void
    UnmapChannel();

    void
    UnmapChannel(int channel);

    void
    UpdateChannel(int channel,
                  int channelElement);

    void
    ResetChannel(int channel);

private:
    std::map<int, VertexResourceChannel> mChannelTable;
};

}
