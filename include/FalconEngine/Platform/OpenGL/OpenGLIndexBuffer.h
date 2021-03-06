#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Platform/OpenGL/OpenGLLib.h>
#include <FalconEngine/Platform/OpenGL/OpenGLBuffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/IndexBuffer.h>

namespace FalconEngine
{

class Renderer;

FALCON_ENGINE_CLASS_BEGIN PlatformIndexBuffer :
public PlatformBuffer
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformIndexBuffer(Renderer * renderer, const IndexBuffer * indexBuffer);
    virtual ~PlatformIndexBuffer();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Enable(Renderer *);

    void
    Disable(Renderer *);
};
FALCON_ENGINE_CLASS_END

}

#endif