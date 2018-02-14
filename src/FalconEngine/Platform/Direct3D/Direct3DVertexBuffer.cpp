#include <FalconEngine/Platform/Direct3D/Direct3DVertexBuffer.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Graphics/Renderer/Resource/VertexBuffer.h>
#include <FalconEngine/Platform/Win32/Win32Exception.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformVertexBuffer::PlatformVertexBuffer(Renderer *renderer, const VertexBuffer *vertexBuffer) :
    PlatformBuffer(renderer, vertexBuffer)
{
}

PlatformVertexBuffer::~PlatformVertexBuffer()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformVertexBuffer::Enable(Renderer *renderer, unsigned bindingIndex, int64_t offset, int stride)
{
    auto strideD3D = UINT(stride);
    auto offsetD3D = UINT(offset);
    renderer->mData->GetContext()->IASetVertexBuffers(bindingIndex, 1, mBufferObj.GetAddressOf(), &strideD3D, &offsetD3D);
}

void
PlatformVertexBuffer::Disable(Renderer *renderer, unsigned bindingIndex)
{
    renderer->mData->GetContext()->IASetVertexBuffers(bindingIndex, 1, nullptr, nullptr, nullptr);
}

}

#endif