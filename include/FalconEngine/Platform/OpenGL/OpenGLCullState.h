#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Platform/OpenGL/OpenGLLib.h>

namespace FalconEngine
{
class CullState;

FALCON_ENGINE_CLASS_BEGIN PlatformCullState
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    PlatformCullState();
    ~PlatformCullState() = default;

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Initialize(const CullState * cullState);

    void
    Set(const CullState * cullState);

public:
    bool mCullEnabled;
    bool mCullCounterClockwise;
};
FALCON_ENGINE_CLASS_END

}

#endif