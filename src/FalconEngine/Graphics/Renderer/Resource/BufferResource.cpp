#include <FalconEngine/Graphics/Renderer/Resource/BufferResource.h>

#include <FalconEngine/Graphics/Renderer/Renderer.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexBuffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexGroup.h>

using namespace std;

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
BufferResource::BufferResource()
{
}

BufferResource::~BufferResource()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
BufferResource::CreateChannel(int                                   channel,
                              const std::shared_ptr<Visual>&        channelVisual,
                              const std::shared_ptr<BufferAdaptor>& channelAdaptor)
{
    if (mChannelTable.find(channel) != mChannelTable.end())
    {
        FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("Channel has been used.");
    }

    if (channelVisual)
    {
        mChannelTable.emplace(channel,
                              BufferResourceChannel(
                                  channelVisual,
                                  channelAdaptor));
    }
    else
    {
        mChannelTable.emplace(channel,
                              BufferResourceChannel(
                                  nullptr,
                                  channelAdaptor));
    }
}

void
BufferResource::Draw(const Camera *camera) const
{
    for (auto& channelInfoPair : mChannelTable)
    {
        auto channel = channelInfoPair.first;
        DrawChannel(channel, camera);
    }
}

void
BufferResource::DrawChannel(int channel, const Camera *camera) const
{
    static auto sMasterRenderer = Renderer::GetInstance();

    sMasterRenderer->Draw(camera, GetChannelVisual(channel));
}

void
BufferResource::FillBegin(BufferAccessMode          access,
                          BufferFlushMode           flush,
                          BufferSynchronizationMode synchronization)
{
    for (auto& channelInfoPair : mChannelTable)
    {
        auto channel = channelInfoPair.first;
        FillChannelBegin(channel, access, flush, synchronization);
    }
}

void
BufferResource::FillChannelBegin(int                       channel,
                                 BufferAccessMode          access,
                                 BufferFlushMode           flush,
                                 BufferSynchronizationMode synchronization)
{
    CheckChannelValid(channel);

    // Must call before mapping.
    mChannelTable.at(channel).mBufferAdaptor->FillBegin();

    MapChannel(channel, access, flush, synchronization);
}

void
BufferResource::FillEnd()
{
    for (auto& channelInfoPair : mChannelTable)
    {
        auto channel = channelInfoPair.first;
        FillChannelEnd(channel);
    }
}

void
BufferResource::FillChannelEnd(int channel)
{
    CheckChannelValid(channel);

    UnmapChannel(channel);

    auto& channelInfo = mChannelTable.at(channel);

    // Must call after mapping.
    channelInfo.mBufferAdaptor->FillEnd();
    channelInfo.mBuffer->SetElementNum(channelInfo.mElementNum);
}

std::tuple<BufferAdaptor *, unsigned char *>
BufferResource::GetChannelData(int channel)
{
    CheckChannelValid(channel);

    auto& channelInfo = mChannelTable.at(channel);
    return std::make_tuple(channelInfo.mBufferAdaptor.get(), channelInfo.mData);
}

const Visual *
BufferResource::GetChannelVisual(int channel) const
{
    CheckChannelValid(channel);

    if (mChannelTable.at(channel).mVisual != nullptr)
    {
        return mChannelTable.at(channel).mVisual.get();
    }
    else
    {
        FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("The channel doesn't have a valid Visual.");
    }
}

void
BufferResource::UpdateChannelElement(int channel, int channelElement)
{
    CheckChannelValid(channel);

    auto& channelInfo = mChannelTable.at(channel);
    channelInfo.mElementNum += channelElement;
}

void
BufferResource::Reset()
{
    for (auto& channelInfoPair : mChannelTable)
    {
        auto channel = channelInfoPair.first;
        ResetChannel(channel);
    }
}

void
BufferResource::ResetChannel(int channel)
{
    CheckChannelValid(channel);

    mChannelTable.at(channel).mData = nullptr;
    mChannelTable.at(channel).mElementNum = 0;
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
void
BufferResource::CheckChannelValid(int channel) const
{
    if (mChannelTable.find(channel) == mChannelTable.end())
    {
        FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("Channel has not been created.");
    }
}

void
BufferResource::Map(BufferAccessMode access, BufferFlushMode flush, BufferSynchronizationMode synchronization)
{
    for (auto& channelInfoPair : mChannelTable)
    {
        auto channel = channelInfoPair.first;
        MapChannel(channel, access, flush, synchronization);
    }
}

void
BufferResource::MapChannel(int channel, BufferAccessMode access, BufferFlushMode flush, BufferSynchronizationMode synchronization)
{
    CheckChannelValid(channel);

    auto& channelInfo = mChannelTable.at(channel);

    // ALERT(Wuxiang): signed, unsigned conversion.
    int64_t size = int64_t(channelInfo.mElementNum)
                   * int64_t(channelInfo.mBuffer->GetElementSize());
    int64_t offset = channelInfo.mBuffer->GetDataOffset();

    static auto sMasterRenderer = Renderer::GetInstance();
    channelInfo.mData = static_cast<unsigned char *>(
                            sMasterRenderer->Map(channelInfo.mBuffer.get(),
                                    access, flush, synchronization,
                                    offset, size));
}

void
BufferResource::Unmap()
{
    for (auto& channelInfoPair : mChannelTable)
    {
        auto channel = channelInfoPair.first;
        UnmapChannel(channel);
    }
}

void
BufferResource::UnmapChannel(int channel)
{
    CheckChannelValid(channel);

    static auto sMasterRenderer = Renderer::GetInstance();
    auto& channelInfo = mChannelTable.at(channel);
    sMasterRenderer->Unmap(channelInfo.mBuffer.get());
}

}
