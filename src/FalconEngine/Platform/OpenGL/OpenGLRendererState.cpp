#include <FalconEngine/Platform/OpenGL/OpenGLRendererState.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Core/Memory.h>
#include <FalconEngine/Graphics/Renderer/State/BlendState.h>
#include <FalconEngine/Graphics/Renderer/State/CullState.h>
#include <FalconEngine/Graphics/Renderer/State/DepthTestState.h>
#include <FalconEngine/Graphics/Renderer/State/OffsetState.h>
#include <FalconEngine/Graphics/Renderer/State/StencilTestState.h>
#include <FalconEngine/Graphics/Renderer/State/WireframeState.h>
#include <FalconEngine/Platform/OpenGL/OpenGLMapping.h>

namespace FalconEngine
{

FALCON_ENGINE_DELETER_DECLARE(PlatformRendererState, PlatformRendererStateDeleter);
FALCON_ENGINE_DELETER_IMPLEMENT(PlatformRendererState, PlatformRendererStateDeleter);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformStencilTestFaceState::PlatformStencilTestFaceState() :
    mDepthTestFailOperation(0), mDepthTestPassOperation(0),
    mStencilTestFailOperation(0), mStencilCompareFunction(0)
{
}

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformRendererState::PlatformRendererState() :
    mBlendEnabled(false), mBlendSourceFactor(0), mBlendSourceFactorAlpha(0),
    mBlendDestinationFactor(0), mBlendDestinationFactorAlpha(0), mBlendOperator(0),
    mBlendOperatorAlpha(0), mLogicEnabled(false), mLogicOperator(0),

    mCullEnabled(false), mCullCounterClockwise(false), mDepthTestEnabled(false),
    mDepthWriteEnabled(false), mDepthCompareFunction(0),

    mOffsetFillEnabled(false),
    mOffsetLineEnabled(false), mOffsetPointEnabled(false), mOffsetFactor(0),
    mOffsetUnit(0),

    mStencilTestEnabled(false), mStencilCompareReference(0), mStencilCompareMask(0),
    mStencilWriteMask(0), mStencilFrontFace(), mStencilBackFace(),

    mWireframeEnabled(false)
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
    InitializeBlendState(blendState);
    InitializeCullState(cullState);
    InitializeDepthTestState(depthTestState);
    InitializeOffsetState(offsetState);
    InitializeStencilTestState(stencilTestState);

    // Wireframe Mode
    mWireframeEnabled = wireframeState->mEnabled;

    glPolygonMode(GL_FRONT_AND_BACK, mWireframeEnabled ? GL_LINE : GL_FILL);
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
void
PlatformRendererState::InitializeBlendState(const BlendState *blendState)
{
    mBlendEnabled = blendState->mEnabled;
    mBlendSourceFactorAlpha = OpenGLBlendFactor[BlendFactorIndex(blendState->mSourceFactorAlpha)];
    mBlendSourceFactor = OpenGLBlendFactor[BlendFactorIndex(blendState->mSourceFactor)];
    mBlendDestinationFactorAlpha = OpenGLBlendFactor[BlendFactorIndex(blendState->mDestinationFactorAlpha)];
    mBlendDestinationFactor = OpenGLBlendFactor[BlendFactorIndex(blendState->mDestinationFactor)];
    mBlendConstantFactor = blendState->mConstantFactor;
    mBlendOperator = OpenGLBlendOperator[BlendOperatorIndex(blendState->mOperator)];
    mLogicEnabled = blendState->mLogicEnabled;
    mLogicOperator = OpenGLLogicOperator[LogicOperatorIndex(blendState->mLogicOperator)];

    mBlendEnabled ? glEnable(GL_BLEND) : glDisable(GL_BLEND);
    glBlendColor(mBlendConstantFactor[0], mBlendConstantFactor[1], mBlendConstantFactor[2],
                 mBlendConstantFactor[3]);
    glBlendFuncSeparate(mBlendSourceFactor, mBlendDestinationFactor,
                        mBlendSourceFactorAlpha, mBlendDestinationFactorAlpha);
    glBlendEquation(mBlendOperator);
    mLogicEnabled ? glEnable(GL_COLOR_LOGIC_OP) : glDisable(GL_COLOR_LOGIC_OP);
    glLogicOp(mLogicOperator);
}

void
PlatformRendererState::InitializeCullState(const CullState *cullState)
{
    mCullEnabled = cullState->mEnabled;
    mCullCounterClockwise = cullState->mCounterClockwise;

    mCullEnabled ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(mCullCounterClockwise ? GL_FRONT : GL_BACK);
}

void
PlatformRendererState::InitializeDepthTestState(const DepthTestState *depthTestState)
{
    mDepthTestEnabled = depthTestState->mEnabled;
    mDepthWriteEnabled = depthTestState->mWriteEnabled;
    mDepthCompareFunction = OpenGLDepthFunction[int(depthTestState->mCompareFunction)];

    mDepthTestEnabled ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);

    // You still need to have to enable depth test to enable writing to depth buffer
    glDepthMask(mDepthWriteEnabled ? GL_TRUE : GL_FALSE);
    glDepthFunc(mDepthCompareFunction);
}

void
PlatformRendererState::InitializeOffsetState(const OffsetState *offsetState)
{
    mOffsetFillEnabled = offsetState->mFillEnabled;
    mOffsetLineEnabled = offsetState->mLineEnabled;
    mOffsetPointEnabled = offsetState->mPointEnabled;
    mOffsetFactor = offsetState->mFactor;
    mOffsetUnit = offsetState->mUnit;

    mOffsetFillEnabled ? glEnable(GL_POLYGON_OFFSET_FILL) : glDisable(GL_POLYGON_OFFSET_FILL);
    mOffsetLineEnabled ? glEnable(GL_POLYGON_OFFSET_LINE) : glDisable(GL_POLYGON_OFFSET_LINE);
    mOffsetPointEnabled ? glEnable(GL_POLYGON_OFFSET_POINT) : glDisable(GL_POLYGON_OFFSET_POINT);
    glPolygonOffset(mOffsetFactor, mOffsetUnit);
}

void
InitializeStencilTestFaceStatePlatform(PlatformStencilTestFaceState& stencilTestFaceStatePlatform, const StencilTestFaceState &stencilTestFaceState)
{
    stencilTestFaceStatePlatform.mStencilCompareFunction = OpenGLStencilFunction[int(stencilTestFaceState.mStencilCompareFunction)];
    stencilTestFaceStatePlatform.mStencilTestFailOperation = OpenGLStencilOperation[int(stencilTestFaceState.mStencilTestFailOperation)];
    stencilTestFaceStatePlatform.mDepthTestFailOperation = OpenGLStencilOperation[int(stencilTestFaceState.mDepthTestFailOperation)];
    stencilTestFaceStatePlatform.mDepthTestPassOperation = OpenGLStencilOperation[int(stencilTestFaceState.mDepthTestPassOperation)];

    glStencilOpSeparate(GL_FRONT,
                        stencilTestFaceStatePlatform.mStencilTestFailOperation,
                        stencilTestFaceStatePlatform.mDepthTestFailOperation,
                        stencilTestFaceStatePlatform.mDepthTestPassOperation);

}

void
PlatformRendererState::InitializeStencilTestState(const StencilTestState *stencilTestState)
{
    mStencilTestEnabled = stencilTestState->mEnabled;
    mStencilCompareReference = stencilTestState->mCompareReference;
    mStencilCompareMask = stencilTestState->mCompareMask;
    mStencilWriteMask = stencilTestState->mWriteMask;

    InitializeStencilTestFaceStatePlatform(mStencilFrontFace, stencilTestState->mFrontFace);
    InitializeStencilTestFaceStatePlatform(mStencilBackFace, stencilTestState->mBackFace);

    mStencilTestEnabled ? glEnable(GL_STENCIL_TEST) : glDisable(GL_STENCIL_TEST);
    glStencilFuncSeparate(GL_FRONT, mStencilFrontFace.mStencilCompareFunction, mStencilCompareReference, mStencilCompareMask);
    glStencilOpSeparate(GL_FRONT, mStencilFrontFace.mStencilTestFailOperation, mStencilFrontFace.mDepthTestFailOperation, mStencilFrontFace.mDepthTestPassOperation);
    glStencilFuncSeparate(GL_BACK, mStencilBackFace.mStencilCompareFunction, mStencilCompareReference, mStencilCompareMask);
    glStencilOpSeparate(GL_BACK, mStencilBackFace.mStencilTestFailOperation, mStencilBackFace.mDepthTestFailOperation, mStencilBackFace.mDepthTestPassOperation);
    glStencilMask(mStencilWriteMask);
}

}

#endif