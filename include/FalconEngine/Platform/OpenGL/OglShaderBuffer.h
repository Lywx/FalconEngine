#pragma once

#include <FalconEngine/Platform/OpenGL/OglMapping.h>
#include <FalconEngine/Platform/OpenGL/OglBuffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/ShaderBuffer.h>

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
