#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Platform/OpenGL/OpenGLLib.h>

namespace FalconEngine
{
class DepthTestState;

FALCON_ENGINE_CLASS_BEGIN PlatformDepthTestState
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    PlatformDepthTestState();
    ~PlatformDepthTestState() = default;

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Initialize(const DepthTestState * depthTestState);

    void
    Set(const DepthTestState * depthTestState);

public:
    bool   mDepthTestEnabled;
    bool   mDepthWriteEnabled;
    GLenum mDepthCompareFunction;
};
FALCON_ENGINE_CLASS_END

}

#endif