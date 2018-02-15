#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Platform/OpenGL/OpenGLLib.h>

namespace FalconEngine
{
class WireframeState;

FALCON_ENGINE_CLASS_BEGIN PlatformWireframeState
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    PlatformWireframeState();
    ~PlatformWireframeState() = default;

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Initialize(const WireframeState * wireframeState);

    void
    Set(const WireframeState * wireframeState);

public:
    bool mWireframeEnabled;
};
FALCON_ENGINE_CLASS_END

}

#endif