#pragma once

#include <FalconEngine/Graphics/Renderer/Platforms/OpenGL/OGLInclude.h>

namespace FalconEngine
{

class VertexFormat;
class PlatformVertexFormat
{
public:
    PlatformVertexFormat(const VertexFormat *vertexFormat);
    ~PlatformVertexFormat();

public:
    void
    Enable();

    void
    Disable();

private:
    GLuint mVertexArray;
};
}
