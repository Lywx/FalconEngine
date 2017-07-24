#pragma once

#include <FalconEngine/Graphics/Renderer/Resource/BufferAdaptor.h>

namespace FalconEngine
{

class FALCON_ENGINE_API BufferCircular : public BufferAdaptor
{
public:
    explicit BufferCircular(const std::shared_ptr<Buffer>& buffer, size_t bufferZoneSize);

protected:
    /************************************************************************/
    /* Protected Members                                                    */
    /************************************************************************/
    virtual void
    FillBegin() override;

    virtual void
    FillEnd() override;

private:
    // Where the data offset should be when the next fill phrase begins.
    size_t mBufferDataOffsetNext;

    // How much data should be keep safely at once without wrapping the data offset.
    size_t mBufferZoneSize;
};

}
