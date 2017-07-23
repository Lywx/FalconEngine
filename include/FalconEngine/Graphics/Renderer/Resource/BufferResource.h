#pragma once

#include <FalconEngine/Graphics/Common.h>

#include <map>
#include <tuple>
#include <unordered_map>

#include <FalconEngine/Graphics/Renderer/Scene/Visual.h>
#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/BufferAdaptor.h>

namespace FalconEngine
{

class Camera;
class Visual;

#pragma warning(disable: 4251)
class BufferResourceChannel
{
public:
    BufferResourceChannel(
        const std::shared_ptr<Visual>& visual,
        const std::shared_ptr<BufferAdaptor>& bufferAdaptor) :
        mVisual(visual),
        mBuffer(bufferAdaptor->GetBuffer()),
        mBufferAdaptor(bufferAdaptor),
        mData(nullptr),
        mElementNum(0)
    {
        // NOTE(Wuxiang): Allow visual to be null when you don't need
        // functionality that need visual involved.

        FALCON_ENGINE_CHECK_NULLPTR(mBuffer);
        FALCON_ENGINE_CHECK_NULLPTR(mBufferAdaptor);

        // NOTE(Wuxiang): Allow buffer binding to be null when the buffer is
        // not vertex buffer.
    }

public:
    std::shared_ptr<Visual>              mVisual;

    std::shared_ptr<Buffer>              mBuffer;
    std::shared_ptr<BufferAdaptor>       mBufferAdaptor;

    unsigned char                       *mData;
    int                                  mElementNum;
};

class FALCON_ENGINE_API BufferResource
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    BufferResource();
    virtual ~BufferResource();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    // @remark When a visual is provided, given adaptor has to connect to a
    // vertex buffer. When given adaptor is connected to buffer that is not
    // vertex buffer, the visual must be null.
    void
    CreateChannel(int                                   channel,
                  const std::shared_ptr<Visual>&        channelVisual,
                  const std::shared_ptr<BufferAdaptor>& channelAdaptor);

    void
    Draw(const Camera *camera) const;

    void
    DrawChannel(int channel, const Camera *camera) const;

    void
    FillBegin(BufferAccessMode          access,
              BufferFlushMode           flush,
              BufferSynchronizationMode synchronization);

    void
    FillChannelBegin(int                       channel,
                     BufferAccessMode          access,
                     BufferFlushMode           flush,
                     BufferSynchronizationMode synchronization);

    void
    FillEnd();

    void
    FillChannelEnd(int channel);

    std::tuple<BufferAdaptor *, unsigned char *>
    GetChannelData(int channel);

    // @remark Only provide const visual pointer rather than the shared_ptr
    // version for efficient use in rendering.
    const Visual *
    GetChannelVisual(int channel) const;

    void
    UpdateChannelElement(int channel,
                         int channelElement);

    void
    Reset();

    void
    ResetChannel(int channel);

private:
    /************************************************************************/
    /* Private Members                                                      */
    /************************************************************************/
    void
    CheckChannelValid(int channel) const;

    // @summary Map all channels registered.
    void
    Map(BufferAccessMode          access,
        BufferFlushMode           flush,
        BufferSynchronizationMode synchronization);

    void
    MapChannel(int                       channel,
               BufferAccessMode          access,
               BufferFlushMode           flush,
               BufferSynchronizationMode synchronization);

    // @summary Unmap all channels registered.
    void
    Unmap();

    void
    UnmapChannel(int channel);

private:
    std::unordered_map<int, BufferResourceChannel> mChannelTable;
};
#pragma warning(default: 4251)

}
