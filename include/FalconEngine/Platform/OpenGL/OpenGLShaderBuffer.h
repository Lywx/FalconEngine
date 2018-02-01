#pragma once

#include <FalconEngine/Platform/OpenGL/OpenGLLib.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Graphics/Renderer/Resource/ShaderBuffer.h>
#include <FalconEngine/Platform/OpenGL/OpenGLBuffer.h>

namespace FalconEngine
{

class FALCON_ENGINE_API PlatformShaderBuffer : public PlatformBuffer
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformShaderBuffer(const ShaderBuffer *StorageBuffer);
    ~PlatformShaderBuffer();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Enable(unsigned int bindingIndex);

    void
    Disable();
};

}

#endif