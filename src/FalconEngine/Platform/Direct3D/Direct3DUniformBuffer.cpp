#include <FalconEngine/Platform/Direct3D/Direct3DUniformBuffer.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Graphics/Renderer/Resource/UniformBuffer.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformUniformBuffer::PlatformUniformBuffer(Renderer *renderer, const UniformBuffer *uniformBuffer) :
    PlatformBuffer(renderer, uniformBuffer)
{
}

PlatformUniformBuffer::~PlatformUniformBuffer()
{
}

}

#endif