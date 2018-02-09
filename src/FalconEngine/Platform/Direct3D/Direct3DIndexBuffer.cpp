#include <FalconEngine/Platform/Direct3D/Direct3DIndexBuffer.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <cstring>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformIndexBuffer::PlatformIndexBuffer(Renderer *renderer, const IndexBuffer *indexBuffer) :
    PlatformBuffer(renderer, indexBuffer)
{
    auto indexType = indexBuffer->GetIndexType();
    if (indexType == IndexType::UnsignedShort)
    {
        mFormat = DXGI_FORMAT_R16_UINT;
    }
    else if (indexType == IndexType::UnsignedInt)
    {
        mFormat = DXGI_FORMAT_R32_UINT;
    }
}

PlatformIndexBuffer::~PlatformIndexBuffer()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformIndexBuffer::Enable(Renderer *renderer)
{
    renderer->mData->GetContext()->IASetIndexBuffer(&mBufferObj, mFormat, 0);

    // TODO(Wuxiang): 2018-02-07 22:47.

}

void
PlatformIndexBuffer::Disable(Renderer *)
{
// TODO(Wuxiang): 2018-02-07 22:47.
}

}
#endif