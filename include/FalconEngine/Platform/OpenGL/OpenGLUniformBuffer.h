#pragma once

#pragma once

#include <FalconEngine/Core/Macro.h>
#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Platform/OpenGL/OpenGLLib.h>
#include <FalconEngine/Platform/OpenGL/OpenGLBuffer.h>

namespace FalconEngine
{

class Renderer;
class UniformBuffer;

FALCON_ENGINE_CLASS_BEGIN PlatformUniformBuffer :
public PlatformBuffer
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformUniformBuffer(Renderer * renderer, const UniformBuffer * uniformBuffer);
    virtual ~PlatformUniformBuffer();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Enable(Renderer *);

    void
    Disable(Renderer *);

    void *
    Map(Renderer *);
};
FALCON_ENGINE_CLASS_END

}

#endif
