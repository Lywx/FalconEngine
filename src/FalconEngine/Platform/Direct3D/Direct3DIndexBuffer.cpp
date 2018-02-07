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
}

PlatformIndexBuffer::~PlatformIndexBuffer()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformIndexBuffer::Enable(Renderer *)
{
    // TODO(Wuxiang): 2018-02-07 22:47.

}

void
PlatformIndexBuffer::Disable(Renderer *)
{
// TODO(Wuxiang): 2018-02-07 22:47.
}

}
#endif