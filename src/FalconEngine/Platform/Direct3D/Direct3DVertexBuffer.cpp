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
    PlatformBuffer(renderer, D3D11_BIND_VERTEX_BUFFER, vertexBuffer)
{
}

PlatformVertexBuffer::~PlatformVertexBuffer()
{
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
// TODO(Wuxiang): 2018-02-07 22:47.
}

#endif