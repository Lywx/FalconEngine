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

public:
    /************************************************************************/
    /* Blending                                                             */
    /************************************************************************/
    bool     mBlendEnabled;
    GLenum   mBlendSourceFactor;
    GLenum   mBlendDestinationFactor;
    Vector4f mBlendConstantFactor;

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
    GLenum mStencilCompareFunction;
    GLuint mStencilCompareReference;
    GLuint mStencilCompareMask;
    GLuint mStencilWriteMask;
    GLenum mStencilOnStencilTestFail;
    GLenum mStencilOnDepthTestFail;
    GLenum mStencilOnDepthTestPass;

    // Wireframe Mode
    bool mWireframeEnabled;
};
FALCON_ENGINE_CLASS_END

}

#endif