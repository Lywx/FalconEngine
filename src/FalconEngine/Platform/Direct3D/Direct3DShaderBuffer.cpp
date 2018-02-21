#include <FalconEngine/Platform/Direct3D/Direct3DShaderBuffer.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Core/Exception.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformShaderBuffer::PlatformShaderBuffer(Renderer *renderer, const ShaderBuffer *shaderBuffer) :
    PlatformBuffer(renderer, shaderBuffer)
{
}

PlatformShaderBuffer::~PlatformShaderBuffer()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformShaderBuffer::Enable(Renderer *, unsigned bindingIndex)
{
    FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
}

void
PlatformShaderBuffer::Disable(Renderer *)
{
    FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
}

}

#endif