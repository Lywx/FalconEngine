#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Platform/OpenGL/OpenGLLib.h>

namespace FalconEngine
{

class StencilTestFaceState;
class StencilTestState;

FALCON_ENGINE_CLASS_BEGIN PlatformStencilTestFaceState
{
public:
    PlatformStencilTestFaceState();
    ~PlatformStencilTestFaceState() = default;

public:
    GLenum mDepthTestFailOperation;
    GLenum mDepthTestPassOperation;
    GLenum mStencilTestFailOperation;
    GLenum mStencilCompareFunction;
};
FALCON_ENGINE_CLASS_END


FALCON_ENGINE_CLASS_BEGIN PlatformStencilTestState
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    PlatformStencilTestState();
    ~PlatformStencilTestState() = default;

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Initialize(const StencilTestState * stencilTestState);

    void
    Set(const StencilTestState * stencilTestState);

private:
    /************************************************************************/
    /* Private Members                                                      */
    /************************************************************************/
    void
    InitializeFaceState(
        _IN_ GLenum face,
        _IN_ const StencilTestFaceState & faceState,
        _OUT_ PlatformStencilTestFaceState & faceStatePlatform);

    void
    SetFaceState(_IN_ GLenum face,
                 _IN_ const StencilTestFaceState & faceStateCurrent,
                 _IN_OUT_ PlatformStencilTestFaceState & faceStatePlatform,
                 _IN_ bool compareMaskChanged,
                 _IN_ bool compareReferenceChanged);

public:
    bool   mStencilTestEnabled;

    GLuint mStencilCompareReference;
    GLuint mStencilCompareMask;
    GLuint mStencilWriteMask;

    PlatformStencilTestFaceState mStencilFrontFace;
    PlatformStencilTestFaceState mStencilBackFace;
};
FALCON_ENGINE_CLASS_END

}

#endif