#pragma once

#include <FalconEngine/Platform/OpenGL/Common.h>
#if defined(FALCON_ENGINE_API_OPENGL)

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

#endif