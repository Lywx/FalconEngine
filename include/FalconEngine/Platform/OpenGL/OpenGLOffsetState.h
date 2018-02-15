#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Math/Vector4.h>
#include <FalconEngine/Platform/OpenGL/OpenGLLib.h>

namespace FalconEngine
{
class OffsetState;

FALCON_ENGINE_CLASS_BEGIN PlatformOffsetState
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    PlatformOffsetState();
    ~PlatformOffsetState() = default;

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Initialize(const OffsetState * offsetState);

    void
    Set(const OffsetState * offsetState);

public:
    bool  mOffsetFillEnabled;
    bool  mOffsetLineEnabled;
    bool  mOffsetPointEnabled;
    float mOffsetFactor;
    float mOffsetUnit;
};
FALCON_ENGINE_CLASS_END

}

#endif