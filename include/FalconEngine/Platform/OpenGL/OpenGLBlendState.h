#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Math/Vector4.h>
#include <FalconEngine/Platform/OpenGL/OpenGLLib.h>

namespace FalconEngine
{
class BlendState;

FALCON_ENGINE_CLASS_BEGIN PlatformBlendState
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    PlatformBlendState();
    ~PlatformBlendState() = default;

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Initialize(const BlendState * blendState);

    void
    Set(const BlendState * blendState);

public:
    bool     mBlendEnabled;
    GLenum   mBlendSourceFactor;
    GLenum   mBlendSourceFactorAlpha;
    GLenum   mBlendDestinationFactor;
    GLenum   mBlendDestinationFactorAlpha;
    Vector4f mBlendConstantFactor;
    GLenum   mBlendOperator;
    GLenum   mBlendOperatorAlpha;

    bool     mLogicEnabled;
    GLenum   mLogicOperator;
};
FALCON_ENGINE_CLASS_END

}

#endif