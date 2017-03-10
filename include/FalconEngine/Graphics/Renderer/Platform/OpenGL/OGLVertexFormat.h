#pragma once

#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLInclude.h>

namespace FalconEngine
{

class VertexFormat;
class PlatformVertexFormat
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    PlatformVertexFormat(const VertexFormat *vertexFormat);
    ~PlatformVertexFormat();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Enable();

    void
    Disable();

private:
    GLuint mVertexArray;
};
}
