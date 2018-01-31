#pragma once

#include <FalconEngine/Core/Macro.h>

#include <map>
#include <tuple>
#include <memory>

#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/BufferAdaptor.h>
#include <FalconEngine/Graphics/Renderer/Resource/BufferResourceChannel.h>
#include <FalconEngine/Graphics/Renderer/Scene/Visual.h>

namespace FalconEngine
{

class BufferResourceChannel
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    BufferResourceChannel(
        const std::shared_ptr<BufferAdaptor>& bufferAdaptor,
        const std::shared_ptr<Visual>& visual);

    virtual ~BufferResourceChannel() = default;

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    virtual void
    Reset();

    virtual void
    ResetPersistent();

    // NOTE(Wuxiang): Internal use.
public:
    std::shared_ptr<Buffer>        mBuffer;
    std::shared_ptr<BufferAdaptor> mBufferAdaptor;

    unsigned char                 *mData;

    int                            mElementNumMapped;
    int                            mElementNumPersistent;

    std::shared_ptr<Visual>        mVisual;
};

}

