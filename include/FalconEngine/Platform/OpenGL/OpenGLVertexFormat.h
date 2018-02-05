#pragma once

#include <FalconEngine/Platform/OpenGL/OpenGLLib.h>

#if defined(FALCON_ENGINE_API_OPENGL)

namespace FalconEngine
{

class Renderer;
class VertexFormat;

class FALCON_ENGINE_API PlatformVertexFormat final
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformVertexFormat(Renderer *, const VertexFormat *vertexFormat);
    ~PlatformVertexFormat();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Enable(Renderer *);

    void
    Disable(Renderer *);

private:
    /************************************************************************/
    /* Private Members                                                      */
    /************************************************************************/
    void
    Create();

private:
    GLuint              mVertexArrayObj;
    const VertexFormat *mVertexFormatPtr;
};
}

#endif