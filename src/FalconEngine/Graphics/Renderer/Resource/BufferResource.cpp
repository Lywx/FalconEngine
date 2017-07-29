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

/************************************************************************/
/* Channel Creation                                                     */
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

/************************************************************************/
/* Element Management                                                   */
/************************************************************************/
void
BufferResource::AddChannelElement(int channel, int channelElement)
{
    CheckChannelValid(channel);

    auto& channelInfo = mChannelTable.at(channel);
    channelInfo.mElementNum += channelElement;
    channelInfo.mElementNumMapped += channelElement;
}

void
BufferResource::AddChannelElementMapping(int channel, int channelElementMapped)
{
    CheckChannelValid(channel);

    auto& channelInfo = mChannelTable.at(channel);
    channelInfo.mElementNumMapped += channelElementMapped;
}

void
BufferResource::ResetElement()
{
    for (auto& channelInfoPair : mChannelTable)
    {
        auto channel = channelInfoPair.first;
        ResetChannelElement(channel);
    }
}

void
BufferResource::ResetChannelElement(int channel)
{
    CheckChannelValid(channel);

    mChannelTable.at(channel).mElementNum = 0;
    mChannelTable.at(channel).mElementNumMapped = 0;
}

void
BufferResource::SetChannelElement(int channel, int channelElement)
{
    CheckChannelValid(channel);

    auto& channelInfo = mChannelTable.at(channel);
    channelInfo.mElementNum = channelElement;
}

/************************************************************************/
/* Draw                                                                 */
/************************************************************************/
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

/************************************************************************/
/* Data Management                                                      */
/************************************************************************/
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

    auto& channelInfo = mChannelTable.at(channel);

    // Must call before mapping.
    channelInfo.mBufferAdaptor->FillBegin();

    if (channelInfo.mElementNumMapped > 0)
    {
        MapChannel(channel, access, flush, synchronization);
    }
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

    auto& channelInfo = mChannelTable.at(channel);
    if (channelInfo.mElementNumMapped > 0)
    {
        UnmapChannel(channel);
    }

    // Must call after mapping.
    channelInfo.mBufferAdaptor->FillEnd();
    channelInfo.mBuffer->SetElementNum(channelInfo.mElementNum);
    channelInfo.mData = nullptr;
}

std::tuple<BufferAdaptor *, unsigned char *>
BufferResource::GetChannelData(int channel)
{
    CheckChannelValid(channel);

    auto& channelInfo = mChannelTable.at(channel);
    return std::make_tuple(channelInfo.mBufferAdaptor.get(), channelInfo.mData);
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
    int64_t size = int64_t(channelInfo.mElementNumMapped)
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

/************************************************************************/
/* Helper Members                                                       */
/************************************************************************/
void
BufferResource::CheckChannelValid(int channel) const
{
    if (mChannelTable.find(channel) == mChannelTable.end())
    {
        FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("Channel has not been created.");
    }
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

}
