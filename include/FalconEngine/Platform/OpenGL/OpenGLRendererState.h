#pragma once

#include <FalconEngine/Platform/OpenGL/OpenGLLib.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Math/Vector4.h>

namespace FalconEngine
{

class BlendState;
class CullState;
class DepthTestState;
class OffsetState;
class StencilTestState;
class WireframeState;

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

// @summary Render state information to avoid redundant state changes.
FALCON_ENGINE_CLASS_BEGIN PlatformRendererState
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    PlatformRendererState();
    ~PlatformRendererState() = default;

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Initialize(const BlendState * blendState,
               const CullState * cullState,
               const DepthTestState * depthTestState,
               const OffsetState * offsetState,
               const StencilTestState * stencilTestState,
               const WireframeState * wireframeState);

private:
    void
    InitializeBlendState(const BlendState * blendState);

    void
    InitializeCullState(const CullState * cullState);

    void
    InitializeDepthTestState(const DepthTestState * depthTestState);

    void
    InitializeOffsetState(const OffsetState * offsetState);

    void
    InitializeStencilTestState(const StencilTestState * stencilTestState);

public:
    /************************************************************************/
    /* Blending                                                             */
    /************************************************************************/
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

    /************************************************************************/
    /* Culling                                                              */
    /************************************************************************/
    bool mCullEnabled;
    bool mCullCounterClockwise;

    /************************************************************************/
    /* Depth Test                                                           */
    /************************************************************************/
    bool   mDepthTestEnabled;
    bool   mDepthWriteEnabled;
    GLenum mDepthCompareFunction;

    /************************************************************************/
    /* Polygon Offset                                                       */
    /************************************************************************/
    bool  mOffsetFillEnabled;
    bool  mOffsetLineEnabled;
    bool  mOffsetPointEnabled;
    float mOffsetFactor;
    float mOffsetUnit;

    /************************************************************************/
    /* Stencil Test                                                         */
    /************************************************************************/
    bool   mStencilTestEnabled;

    GLuint mStencilCompareReference;
    GLuint mStencilCompareMask;
    GLuint mStencilWriteMask;

    PlatformStencilTestFaceState mStencilFrontFace;
    PlatformStencilTestFaceState mStencilBackFace;

    /************************************************************************/
    /* Wireframe                                                            */
    /************************************************************************/
    bool mWireframeEnabled;
};
FALCON_ENGINE_CLASS_END

}

#endif