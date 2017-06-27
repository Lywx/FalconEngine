#pragma once

#include <FalconEngine/Graphics/Renderer/Resource/BufferAdaptor.h>

namespace FalconEngine
{

class FALCON_ENGINE_API BufferCircular : BufferAdaptor
{
public:
    explicit BufferCircular(std::shared_ptr<Buffer> buffer, size_t bufferZoneByteNum);

protected:
    /************************************************************************/
    /* Protected Members                                                    */
    /************************************************************************/
    virtual void
    FillBegin() override;

    virtual void
    FillEnd() override;

private:
    size_t mBufferZoneByteNum;
};

}
