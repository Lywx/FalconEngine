#include <FalconEngine/Graphics/Renderer/Resource/VertexResource.h>

#include <FalconEngine/Graphics/Renderer/Renderer.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
VertexResource::VertexResource()
{
}

VertexResource::~VertexResource()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
VertexResource::CreateChannel(int                            channel,
                              std::shared_ptr<BufferAdaptor> channelAdaptor,
                              std::shared_ptr<Visual>        channelVisual)
{
    if (mChannelTable.find(channel) != mChannelTable.end())
    {
        FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("Channel has been used.");
    }

    mChannelTable.emplace(channel,
                          channelAdaptor,
                          channelAdaptor->GetBuffer(),
                          channelVisual);
}

void
VertexResource::CheckChannelValid(int channel) const
{
    if (mChannelTable.find(channel) == mChannelTable.end())
    {
        FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("Channel has not been created.");
    }
}

std::tuple<BufferAdaptor *, unsigned char *>
VertexResource::GetChannelData(int channel)
{
    CheckChannelValid(channel);

    auto& channelInfo = mChannelTable.at(channel);
    return std::make_tuple(channelInfo.mBufferAdaptor.get(), channelInfo.mData);
}

const Visual *
VertexResource::GetChannelVisual(int channel) const
{
    CheckChannelValid(channel);

    return mChannelTable.at(channel).mVisual.get();
}

void
VertexResource::MapChannel(BufferAccessMode access, BufferFlushMode flush, BufferSynchronizationMode synchronization)
{
    for (auto& channelInfoPair : mChannelTable)
    {
        auto channel = channelInfoPair.first;
        MapChannel(channel, access, flush, synchronization);
    }
}

void
VertexResource::MapChannel(int channel, BufferAccessMode access, BufferFlushMode flush, BufferSynchronizationMode synchronization)
{
    CheckChannelValid(channel);

    auto& channelInfo = mChannelTable.at(channel);

    auto size = channelInfo.mElementNum * channelInfo.mBuffer->GetElementSize();
    auto offset = channelInfo.mBuffer->GetDataOffset();

    static auto sMasterRenderer = Renderer::GetInstance();
    channelInfo.mData = static_cast<unsigned char *>(
                            sMasterRenderer->Map(channelInfo.mBuffer.get(),
                                    access, flush, synchronization,
                                    offset, size));
}

void
VertexResource::UnmapChannel()
{
    for (auto& channelInfoPair : mChannelTable)
    {
        auto channel = channelInfoPair.first;
        UnmapChannel(channel);
    }
}

void
VertexResource::UnmapChannel(int channel)
{
    CheckChannelValid(channel);

    auto& channelInfo = mChannelTable.at(channel);

    static auto sMasterRenderer = Renderer::GetInstance();
    sMasterRenderer->Unmap(channelInfo.mBuffer.get());

    ResetChannel(channel);
}

void
VertexResource::UpdateChannel(int channel, int channelElement)
{
    CheckChannelValid(channel);

    auto& channelInfo = mChannelTable.at(channel);
    channelInfo.mElementNum += channelElement;
    channelInfo.mBuffer->Get
}

void
VertexResource::ResetChannel(int channel)
{
    CheckChannelValid(channel);

    mChannelTable.at(channel).mData = nullptr;
    mChannelTable.at(channel).mElementNum = 0;
}

}
