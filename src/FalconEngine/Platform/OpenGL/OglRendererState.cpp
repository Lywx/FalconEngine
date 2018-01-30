#include <FalconEngine/Platform/OpenGL/OglRendererState.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Graphics/Renderer/State/BlendState.h>
#include <FalconEngine/Graphics/Renderer/State/CullState.h>
#include <FalconEngine/Graphics/Renderer/State/DepthTestState.h>
#include <FalconEngine/Graphics/Renderer/State/OffsetState.h>
#include <FalconEngine/Graphics/Renderer/State/StencilTestState.h>
#include <FalconEngine/Graphics/Renderer/State/WireframeState.h>
#include <FalconEngine/Platform/OpenGL/OglMapping.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformRendererState::PlatformRendererState() :
    mBlendEnabled(false), mBlendSourceFactor(0), mBlendDestinationFactor(0),
    mCullEnabled(false), mCullCounterClockwise(false), mDepthTestEnabled(false),
    mDepthWriteEnabled(false), mDepthCompareFunction(0), mOffsetFillEnabled(false),
    mOffsetLineEnabled(false), mOffsetPointEnabled(false), mOffsetFactor(0),
    mOffsetUnit(0), mStencilTestEnabled(false), mStencilCompareFunction(0),
    mStencilCompareReference(0), mStencilCompareMask(0), mStencilWriteMask(0),
    mStencilOnStencilTestFail(0), mStencilOnDepthTestFail(0),
    mStencilOnDepthTestPass(0), mWireframeEnabled(false)
{
    // Initialization must be deferred until an OpenGL context has been
    // created.
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformRendererState::Initialize(const BlendState *blendState,
                                  const CullState *cullState,
                                  const DepthTestState *depthTestState,
                                  const OffsetState *offsetState,
                                  const StencilTestState *stencilTestState,
                                  const WireframeState *wireframeState)
{
    // NOTE(Wuxiang): Alpha Test is deprecated after OpenGL 3.0

    // Blending
    mBlendEnabled = blendState->mEnabled;
    mBlendSourceFactor = OpenGLBlendFactorSource[int(blendState->mSourceFactor)];
    mBlendDestinationFactor = OpenGLBlendFactorDestination[int(blendState->mDestinationFactor)];
    mBlendConstantFactor = blendState->mConstantFactor;

    mBlendEnabled ? glEnable(GL_BLEND) : glDisable(GL_BLEND);
    glBlendFunc(mBlendSourceFactor, mBlendDestinationFactor);
    glBlendColor(mBlendConstantFactor[0], mBlendConstantFactor[1], mBlendConstantFactor[2],
                 mBlendConstantFactor[3]);

    // Culling
    mCullEnabled = cullState->mEnabled;
    mCullCounterClockwise = cullState->mCounterClockwise;

    mCullEnabled ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(mCullCounterClockwise ? GL_FRONT : GL_BACK);

    // Depth Test
    mDepthTestEnabled = depthTestState->mTestEnabled;
    mDepthWriteEnabled = depthTestState->mWriteEnabled;
    mDepthCompareFunction = OpenGLDepthFunction[int(depthTestState->mCompareFunction)];

    mDepthTestEnabled ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);

    // You still need to have to enable depth test to enable writing to depth buffer
    glDepthMask(mDepthWriteEnabled ? GL_TRUE : GL_FALSE);
    glDepthFunc(mDepthCompareFunction);

    // Offset State
    mOffsetFillEnabled = offsetState->mFillEnabled;
    mOffsetLineEnabled = offsetState->mLineEnabled;
    mOffsetPointEnabled = offsetState->mPointEnabled;
    mOffsetFactor = offsetState->mFactor;
    mOffsetUnit = offsetState->mUnit;

    mOffsetFillEnabled ? glEnable(GL_POLYGON_OFFSET_FILL) : glDisable(GL_POLYGON_OFFSET_FILL);
    mOffsetLineEnabled ? glEnable(GL_POLYGON_OFFSET_LINE) : glDisable(GL_POLYGON_OFFSET_LINE);
    mOffsetPointEnabled ? glEnable(GL_POLYGON_OFFSET_POINT) : glDisable(GL_POLYGON_OFFSET_POINT);
    glPolygonOffset(mOffsetFactor, mOffsetUnit);

    // Stencil Test
    mStencilTestEnabled = stencilTestState->mTestEnabled;
    mStencilCompareFunction = OpenGLStencilFunction[int(stencilTestState->mCompareFunction)];
    mStencilCompareReference = stencilTestState->mCompareReference;
    mStencilCompareMask = stencilTestState->mCompareMask;
    mStencilWriteMask = stencilTestState->mWriteMask;
    mStencilOnStencilTestFail = OpenGLStencilOperation[int(stencilTestState->OnStencilTestFail)];
    mStencilOnDepthTestFail = OpenGLStencilOperation[int(stencilTestState->OnDepthTestFail)];
    mStencilOnDepthTestPass = OpenGLStencilOperation[int(stencilTestState->OnDepthTestPass)];

    mStencilTestEnabled ? glEnable(GL_STENCIL_TEST) : glDisable(GL_STENCIL_TEST);
    glStencilFunc(mStencilCompareFunction, mStencilCompareReference, mStencilCompareMask);
    glStencilMask(mStencilWriteMask);
    glStencilOp(mStencilOnStencilTestFail, mStencilOnDepthTestFail, mStencilOnDepthTestPass);

    // Wireframe Mode
    mWireframeEnabled = wireframeState->mEnabled;

    glPolygonMode(GL_FRONT_AND_BACK, mWireframeEnabled ? GL_LINE : GL_FILL);
}

}

#endif