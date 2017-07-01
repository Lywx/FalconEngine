#pragma once

#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLMapping.h>
#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLBuffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/IndexBuffer.h>

namespace FalconEngine
{

class FALCON_ENGINE_API PlatformIndexBuffer : public PlatformBuffer
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformIndexBuffer(const IndexBuffer *indexBuffer);
    ~PlatformIndexBuffer();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Enable();

    void
    Disable();
};

}
