#pragma once

#include <FalconEngine/Graphics/Renderer/Resource/BufferAdaptor.h>

namespace FalconEngine
{

class FALCON_ENGINE_API BufferCircular : public BufferAdaptor
{
public:
    explicit BufferCircular(std::shared_ptr<Buffer> buffer, size_t bufferZoneSize);

protected:
    /************************************************************************/
    /* Protected Members                                                    */
    /************************************************************************/
    virtual void
    FillBegin() override;

    virtual void
    FillEnd() override;

private:
    size_t mBufferDataOffsetNext; // Where the data offset should be when the next fill phrase begins.
    size_t mBufferZoneSize;    // How much data should be keep safely at once without wrapping the data offset.
};

}
