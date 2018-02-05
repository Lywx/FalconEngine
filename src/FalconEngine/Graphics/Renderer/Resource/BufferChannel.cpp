#include <FalconEngine/Graphics/Renderer/Resource/BufferChannel.h>

#include <FalconEngine/Core/Exception.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
BufferChannel::BufferChannel(
    const std::shared_ptr<BufferAdaptor>& bufferAdaptor,
    const std::shared_ptr<Visual>&        visual):
    mBuffer(bufferAdaptor->GetBuffer()),
    mBufferAdaptor(bufferAdaptor),
    mData(nullptr),
    mElementNumMapped(0),
    mElementNumPersistent(0),
    mVisual(visual)
{
    // NOTE(Wuxiang): Allow visual to be null when you don't need
    // functionality that need visual involved.

    FALCON_ENGINE_CHECK_NULLPTR(mBuffer);
    FALCON_ENGINE_CHECK_NULLPTR(mBufferAdaptor);

    // NOTE(Wuxiang): Allow buffer binding to be null when the buffer is
    // not vertex buffer.
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
BufferChannel::Reset()
{
    mElementNumMapped = 0;
}

void
BufferChannel::ResetPersistent()
{
    mElementNumPersistent = 0;
}

}
