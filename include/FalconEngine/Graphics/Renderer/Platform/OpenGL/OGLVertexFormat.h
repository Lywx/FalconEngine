#pragma once

#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLMapping.h>

namespace FalconEngine
{

class VertexFormat;
class FALCON_ENGINE_API PlatformVertexFormat
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformVertexFormat(const VertexFormat *vertexFormat);
    ~PlatformVertexFormat();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Enable();

    void
    Disable();

    /************************************************************************/
    /* Private Members                                                      */
    /************************************************************************/
private:
    void
    Create();

private:
    GLuint              mVertexArrayObj;
    const VertexFormat *mVertexFormatPtr;
};
}
