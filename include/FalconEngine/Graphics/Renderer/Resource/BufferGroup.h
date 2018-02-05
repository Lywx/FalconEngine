#pragma once

#include <FalconEngine/Core/Macro.h>

#include <map>
#include <tuple>
#include <unordered_map>

#include <FalconEngine/Core/Exception.h>
#include <FalconEngine/Graphics/Renderer/Renderer.h>
#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/BufferAdaptor.h>
#include <FalconEngine/Graphics/Renderer/Resource/BufferChannel.h>
#include <FalconEngine/Graphics/Renderer/Scene/Visual.h>

namespace FalconEngine
{

class Camera;

FALCON_ENGINE_PROGMA_BEGIN
template <typename T>
class FALCON_ENGINE_API BufferGroup
{
private:
    using BufferChannelSp = const std::shared_ptr<T>&;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    BufferGroup()
    {
        static_assert(std::is_base_of<BufferChannel, T>::value,
                      "Template parameter must inherit from BufferChannel.");
    }

    virtual ~BufferGroup()
    {
    }

public:
    /************************************************************************/
    /* Channel Management                                                   */
    /************************************************************************/
    // @remark When a visual is provided, given adaptor has to connect to a
    // vertex buffer. When given adaptor is connected to buffer that is not
    // vertex buffer, the visual must be null.
    template <typename ... Args>
    const std::shared_ptr<T>&
    CreateChannel(intptr_t                              channel,
                  const std::shared_ptr<BufferAdaptor>& channelAdaptor,
                  const std::shared_ptr<Visual>&        channelVisual,
                  const Args & ...                       channelArgs)
    {
        if (ContainChannel(channel))
        {
            FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("Channel has been used.");
        }

        mChannelTable.emplace(channel, std::make_shared<T>(channelAdaptor, channelVisual, channelArgs ...));
        return mChannelTable.find(channel)->second;
    }

    bool
    ContainChannel(intptr_t channel) const
    {
        return mChannelTable.find(channel) != mChannelTable.end();
    }

    const std::shared_ptr<T>&
    GetChannel(intptr_t channel)
    {
        return mChannelTable.at(channel);
    }

    void
    ReleaseChannel(intptr_t channel)
    {
        auto channelIter = mChannelTable.find(channel);
        if (channelIter != mChannelTable.end())
        {
            mChannelTable.erase(channelIter);
        }
    }

    /************************************************************************/
    /* Element Management                                                   */
    /************************************************************************/
    void
    AddChannelElement(intptr_t channel, int elementNum)
    {
        BufferChannelSp& channelInfo = mChannelTable.at(channel);
        channelInfo->mElementNumMapped += elementNum;
        channelInfo->mElementNumPersistent += elementNum;
    }

    void
    AddChannelElementMapped(intptr_t channel, int elementNumMapped)
    {
        BufferChannelSp channelInfo = mChannelTable.at(channel);
        channelInfo->mElementNumMapped += elementNumMapped;
    }

    void
    AddChannelElementPersistent(intptr_t channel, int elementNumPersistent)
    {
        BufferChannelSp channelInfo = mChannelTable.at(channel);
        channelInfo->mElementNumPersistent += elementNumPersistent;
    }

    int
    GetChannelElementNumPersistent(intptr_t channel)
    {
        BufferChannelSp channelInfo = mChannelTable.at(channel);
        return channelInfo->mElementNumPersistent;
    }

    int
    GetChannelElementNumMapped(intptr_t channel)
    {
        BufferChannelSp channelInfo = mChannelTable.at(channel);
        return channelInfo->mElementNumMapped;
    }

    /************************************************************************/
    /* Item Management                                                      */
    /************************************************************************/
    template <typename ... Args>
    void
    AddChannelItem(intptr_t channel, Args&& ... channelArgs)
    {
        BufferChannelSp channelInfo = mChannelTable.at(channel);

        // NOTE(Wuxiang): Require inherit class to implement extra Add function
        // to support this.
        channelInfo->AddItem(std::move(channelArgs) ...);
    }

    template <typename ... Args>
    void
    AddChannelItem(intptr_t channel, const Args & ... channelArgs)
    {
        BufferChannelSp channelInfo = mChannelTable.at(channel);

        // NOTE(Wuxiang): Require inherit class to implement extra Add function
        // to support this.
        channelInfo->AddItem(channelArgs ...);
    }

    /************************************************************************/
    /* Reset Operations                                                     */
    /************************************************************************/
    // @summary Reset non-persistent channel data for all channel.
    // @remark You usually need to call Reset after FillDataEnd.
    void
    Reset()
    {
        for (auto& channelInfoPair : mChannelTable)
        {
            auto channel = channelInfoPair.first;
            ResetChannel(channel);
        }
    }

    // @summary Reset non-persistent channel data.
    // @remark You usually need to call ResetChannel after FillChannelDataEnd.
    void
    ResetChannel(intptr_t channel)
    {
        BufferChannelSp channelInfo = mChannelTable.at(channel);
        channelInfo->Reset();
    }

    // @summary Reset persistent channel data for all channel.
    void
    ResetPersistent()
    {
        for (auto& channelInfoPair : mChannelTable)
        {
            auto channel = channelInfoPair.first;
            ResetChannelPersistent(channel);
        }
    }

    // @summary Reset persistent channel data.
    void
    ResetChannelPersistent(intptr_t channel)
    {
        BufferChannelSp channelInfo = mChannelTable.at(channel);
        channelInfo->ResetPersistent();
    }

    /************************************************************************/
    /* Draw Operations                                                      */
    /************************************************************************/
    void
    Draw(const Camera *camera) const
    {
        for (auto& channelInfoPair : mChannelTable)
        {
            auto channel = channelInfoPair.first;
            DrawChannel(channel, camera);
        }
    }

    void
    DrawChannel(intptr_t channel, const Camera *camera) const
    {
        static auto sMasterRenderer = Renderer::GetInstance();

        BufferChannelSp channelInfo = mChannelTable.at(channel);

        if (channelInfo->mElementNumPersistent > 0)
        {
            sMasterRenderer->Draw(camera, GetChannelVisual(channel));
        }
    }

    /************************************************************************/
    /* Data Management                                                      */
    /************************************************************************/
    void
    FillDataBegin(ResourceMapAccessMode access,
                  ResourceMapFlushMode flush,
                  ResourceMapSyncMode sync)
    {
        for (auto& channelInfoPair : mChannelTable)
        {
            auto channel = channelInfoPair.first;
            FillChannelDataBegin(channel, access, flush, sync);
        }
    }

    void
    FillChannelDataBegin(intptr_t channel,
                         ResourceMapAccessMode access,
                         ResourceMapFlushMode flush,
                         ResourceMapSyncMode sync)
    {
        BufferChannelSp channelInfo = mChannelTable.at(channel);

        // Must call before mapping.
        channelInfo->mBufferAdaptor->FillBegin();

        if (channelInfo->mElementNumMapped > 0)
        {
            MapChannelData(channel, access, flush, sync);
        }
    }

    // @remark You usually need to call Reset after FillDataEnd.
    void
    FillDataEnd()
    {
        for (auto& channelInfoPair : mChannelTable)
        {
            auto channel = channelInfoPair.first;
            FillChannelDataEnd(channel);
        }
    }

    // @remark If you use *Mapped version of element number management method,
    // you have to set correct persistent element number before calling
    // this method to correctly update element number.
    // @remark You usually need to call ResetChannel after FillChannelDataEnd.
    void
    FillChannelDataEnd(intptr_t channel)
    {
        BufferChannelSp channelInfo = mChannelTable.at(channel);
        if (channelInfo->mElementNumMapped > 0)
        {
            UnmapChannelData(channel);
        }

        // Must call after mapping.
        channelInfo->mBufferAdaptor->FillEnd();

        // NOTE(Wuxiang): Make it possible to call Draw on Visual without extra
        // operations.
        channelInfo->mBuffer->SetElementNum(channelInfo->mElementNumPersistent);
        channelInfo->mData = nullptr;
    }

    void
    FlushChannelData(intptr_t channel, int elementNum)
    {
        BufferChannelSp channelInfo = mChannelTable.at(channel);
        auto buffer = channelInfo->mBuffer.get();

        int64_t size = int64_t(elementNum)
                       * int64_t(channelInfo->mBuffer->GetElementSize());

        static auto sMasterRenderer = Renderer::GetInstance();
        sMasterRenderer->Flush(buffer, 0, size);
    }

    std::tuple<BufferAdaptor *, unsigned char *>
    GetChannelData(intptr_t channel)
    {
        BufferChannelSp channelInfo = mChannelTable.at(channel);
        return std::make_tuple(channelInfo->mBufferAdaptor.get(), channelInfo->mData);
    }

private:
    // @summary Map all channels registered.
    void
    MapData(ResourceMapAccessMode access,
            ResourceMapFlushMode flush,
            ResourceMapSyncMode sync)
    {
        for (auto& channelInfoPair : mChannelTable)
        {
            auto channel = channelInfoPair.first;
            MapChannelData(channel, access, flush, sync);
        }
    }

    void
    MapChannelData(intptr_t channel,
                   ResourceMapAccessMode access,
                   ResourceMapFlushMode flush,
                   ResourceMapSyncMode sync)
    {
        BufferChannelSp channelInfo = mChannelTable.at(channel);

        auto buffer = channelInfo->mBuffer.get();

        // ALERT(Wuxiang): signed, unsigned conversion.
        int64_t size = int64_t(channelInfo->mElementNumMapped)
                       * int64_t(buffer->GetElementSize());
        int64_t offset = buffer->GetDataOffset();

        static auto sMasterRenderer = Renderer::GetInstance();
        channelInfo->mData = static_cast<unsigned char *>(
                                 sMasterRenderer->Map(
                                     buffer, access, flush, sync,
                                     offset, size));
    }

    // @summary Unmap all channels registered.
    void
    UnmapData()
    {
        for (auto& channelInfoPair : mChannelTable)
        {
            auto channel = channelInfoPair.first;
            UnmapChannelData(channel);
        }
    }

    void
    UnmapChannelData(intptr_t channel)
    {
        static auto sMasterRenderer = Renderer::GetInstance();
        BufferChannelSp channelInfo = mChannelTable.at(channel);
        sMasterRenderer->Unmap(channelInfo->mBuffer.get());
    }

    /************************************************************************/
    /* Helper Members                                                       */
    /************************************************************************/
    // @remark Only provide const visual pointer rather than the shared_ptr
    // version for efficient use in rendering.
    const Visual *
    GetChannelVisual(intptr_t channel) const
    {
        BufferChannelSp channelInfo = mChannelTable.at(channel);
        if (channelInfo->mVisual != nullptr)
        {
            return channelInfo->mVisual.get();
        }
        else
        {
            FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("Channel doesn't have a valid Visual.");
        }
    }

public:
    typename std::unordered_map<intptr_t, std::shared_ptr<T>>::iterator
            GetChannelBegin()
    {
        return mChannelTable.begin();
    }

    typename std::unordered_map<intptr_t, std::shared_ptr<T>>::iterator
            GetChannelEnd()
    {
        return mChannelTable.end();
    }

    typename std::unordered_map<intptr_t, std::shared_ptr<T>>::const_iterator
            GetChannelBegin() const
    {
        return mChannelTable.cbegin();
    }

    typename std::unordered_map<intptr_t, std::shared_ptr<T>>::const_iterator
            GetChannelEnd() const
    {
        return mChannelTable.cend();
    }

private:
    std::unordered_map<intptr_t, std::shared_ptr<T>> mChannelTable;
};
FALCON_ENGINE_PROGMA_END

}
