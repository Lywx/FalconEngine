#include <FalconEngine/Graphics/Renderer/Renderer.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Core/Exception.h>
#include <FalconEngine/Graphics/Renderer/PrimitiveLines.h>
#include <FalconEngine/Graphics/Renderer/PrimitivePoints.h>
#include <FalconEngine/Graphics/Renderer/PrimitiveTriangles.h>
#include <FalconEngine/Graphics/Renderer/Resource/IndexBuffer.h>
#include <FalconEngine/Graphics/Renderer/Scene/Visual.h>
#include <FalconEngine/Graphics/Renderer/State/CullState.h>
#include <FalconEngine/Graphics/Renderer/State/OffsetState.h>
#include <FalconEngine/Graphics/Renderer/State/WireframeState.h>
#include <FalconEngine/Platform/OpenGL/OpenGLMapping.h>
#include <FalconEngine/Platform/OpenGL/OpenGLRendererState.h>

using namespace std;

namespace FalconEngine
{

/************************************************************************/
/* State Management                                                     */
/************************************************************************/
void
Renderer::SetBlendStatePlatform(const BlendState *blendState)
{
    FALCON_ENGINE_CHECK_NULLPTR(blendState);

    mBlendStateCurrent = blendState;

    if (mBlendStateCurrent->mEnabled)
    {
        if (!mState->mBlendEnabled)
        {
            mState->mBlendEnabled = true;
            glEnable(GL_BLEND);
        }

        GLenum sourceFactorAlpha = OpenGLBlendFactor[BlendFactorIndex(mBlendStateCurrent->mSourceFactorAlpha)];
        GLenum sourceFactor = OpenGLBlendFactor[BlendFactorIndex(mBlendStateCurrent->mSourceFactor)];
        GLenum destinationFactor = OpenGLBlendFactor[BlendFactorIndex(mBlendStateCurrent->mDestinationFactor)];
        GLenum destinationFactorAlpha = OpenGLBlendFactor[BlendFactorIndex(mBlendStateCurrent->mDestinationFactorAlpha)];
        if (sourceFactor != mState->mBlendSourceFactor
                || sourceFactorAlpha != mState->mBlendSourceFactorAlpha
                || destinationFactor != mState->mBlendDestinationFactor
                || destinationFactorAlpha != mState->mBlendDestinationFactorAlpha)
        {
            mState->mBlendSourceFactor = sourceFactor;
            mState->mBlendSourceFactorAlpha = sourceFactorAlpha;
            mState->mBlendDestinationFactor = destinationFactor;
            mState->mBlendDestinationFactorAlpha = destinationFactorAlpha;
            glBlendFuncSeparate(sourceFactor, destinationFactor, sourceFactorAlpha, destinationFactorAlpha);
        }

        if (mBlendStateCurrent->mConstantFactor != mState->mBlendConstantFactor)
        {
            mState->mBlendConstantFactor = mBlendStateCurrent->mConstantFactor;
            glBlendColor(
                mState->mBlendConstantFactor[0],
                mState->mBlendConstantFactor[1],
                mState->mBlendConstantFactor[2],
                mState->mBlendConstantFactor[3]);
        }

        auto blendOperator = OpenGLBlendOperator[BlendOperatorIndex(mBlendStateCurrent->mOperator)];
        auto blendOperatorAlpha = OpenGLBlendOperator[BlendOperatorIndex(mBlendStateCurrent->mOperatorAlpha)];
        if (blendOperator != mState->mBlendOperator
                || blendOperatorAlpha != mState->mBlendOperatorAlpha)
        {
            mState->mBlendOperator = blendOperator;
            mState->mBlendOperatorAlpha = blendOperatorAlpha;
            glBlendEquationSeparate(blendOperator, blendOperatorAlpha);
        }

        if (mBlendStateCurrent->mLogicEnabled)
        {
            if (!mState->mLogicEnabled)
            {
                mState->mLogicEnabled = true;
                glEnable(GL_COLOR_LOGIC_OP);
            }

            auto logicOperator = OpenGLLogicOperator[LogicOperatorIndex(mBlendStateCurrent->mLogicOperator)];
            if (logicOperator != mState->mLogicOperator)
            {
                mState->mLogicOperator = logicOperator;
                glLogicOp(logicOperator);
            }
        }
        else if (mState->mLogicEnabled)
        {
            mState->mLogicEnabled = false;
            glDisable(GL_COLOR_LOGIC_OP);
        }
    }
    else if (mState->mBlendEnabled)
    {
        mState->mBlendEnabled = false;
        glDisable(GL_BLEND);
    }
}

void
Renderer::SetCullStatePlatform(const CullState *cullState)
{
    FALCON_ENGINE_CHECK_NULLPTR(cullState);

    mCullStateCurrent = cullState;

    if (mCullStateCurrent->mEnabled)
    {
        if (!mState->mCullEnabled)
        {
            mState->mCullEnabled = true;
            glEnable(GL_CULL_FACE);
            glFrontFace(GL_CCW);
            glCullFace(GL_BACK);
        }

        bool cullCounterClockwise = mCullStateCurrent->mCounterClockwise;
        if (cullCounterClockwise != mState->mCullCounterClockwise)
        {
            mState->mCullCounterClockwise = cullCounterClockwise;
            if (mState->mCullCounterClockwise)
            {
                glCullFace(GL_FRONT);
            }
            else
            {
                glCullFace(GL_BACK);
            }
        }
    }
    else if (mState->mCullEnabled)
    {
        mState->mCullEnabled = false;
        glDisable(GL_CULL_FACE);
    }
}

void
Renderer::SetDepthTestStatePlatform(const DepthTestState *depthTestState)
{
    FALCON_ENGINE_CHECK_NULLPTR(depthTestState);

    mDepthTestStateCurrent = depthTestState;

    if (mDepthTestStateCurrent->mEnabled)
    {
        if (!mState->mDepthTestEnabled)
        {
            mState->mDepthTestEnabled = true;
            glEnable(GL_DEPTH_TEST);
        }

        GLenum compareFunction = OpenGLDepthFunction[int(mDepthTestStateCurrent->mCompareFunction)];
        if (compareFunction != mState->mDepthCompareFunction)
        {
            mState->mDepthCompareFunction = compareFunction;
            glDepthFunc(compareFunction);
        }
    }
    else if (mState->mDepthTestEnabled)
    {
        mState->mDepthTestEnabled = false;
        glDisable(GL_DEPTH_TEST);
    }

    if (mDepthTestStateCurrent->mWriteEnabled)
    {
        if (!mState->mDepthWriteEnabled)
        {
            mState->mDepthWriteEnabled = true;
            glDepthMask(GL_TRUE);
        }
    }
    else if (mState->mDepthWriteEnabled)
    {
        mState->mDepthWriteEnabled = false;
        glDepthMask(GL_FALSE);
    }
}

void
Renderer::SetOffsetStatePlatform(const OffsetState *offsetState)
{
    FALCON_ENGINE_CHECK_NULLPTR(offsetState);

    mOffsetStateCurrent = offsetState;

    if (mOffsetStateCurrent->mFillEnabled)
    {
        if (!mState->mOffsetFillEnabled)
        {
            mState->mOffsetFillEnabled = true;
            glEnable(GL_POLYGON_OFFSET_FILL);
        }
    }
    else if (mState->mOffsetFillEnabled)
    {
        mState->mOffsetFillEnabled = false;
        glDisable(GL_POLYGON_OFFSET_FILL);
    }

    if (mOffsetStateCurrent->mLineEnabled)
    {
        if (!mState->mOffsetLineEnabled)
        {
            mState->mOffsetLineEnabled = true;
            glEnable(GL_POLYGON_OFFSET_LINE);
        }
    }
    else if (mState->mOffsetLineEnabled)
    {
        mState->mOffsetLineEnabled = false;
        glDisable(GL_POLYGON_OFFSET_LINE);
    }

    if (mOffsetStateCurrent->mPointEnabled)
    {
        if (!mState->mOffsetPointEnabled)
        {
            mState->mOffsetPointEnabled = true;
            glEnable(GL_POLYGON_OFFSET_POINT);
        }
    }
    else if (mState->mOffsetPointEnabled)
    {
        mState->mOffsetPointEnabled = false;
        glDisable(GL_POLYGON_OFFSET_POINT);
    }

    if (mOffsetStateCurrent->mFactor != mState->mOffsetFactor
            || mOffsetStateCurrent->mUnit != mState->mOffsetUnit)
    {
        mState->mOffsetFactor = mOffsetStateCurrent->mFactor;
        mState->mOffsetUnit = mOffsetStateCurrent->mUnit;
        glPolygonOffset(mOffsetStateCurrent->mFactor, mOffsetStateCurrent->mUnit);
    }
}

void
SetStencilTestFaceStatePlatform(_IN_ const PlatformRendererState *rendererState,
                                _IN_ GLenum face,
                                _IN_ const StencilTestFaceState& faceStateCurrent,
                                _IN_OUT_ PlatformStencilTestFaceState& faceStatePlatform,
                                _IN_ bool compareMaskChanged,
                                _IN_ bool compareReferenceChanged)
{
    GLenum compareFunction = OpenGLStencilFunction[StencilFunctionIndex(
                                 faceStateCurrent.mStencilCompareFunction)];
    if (compareFunction != faceStatePlatform.mStencilCompareFunction
            || compareMaskChanged
            || compareReferenceChanged)
    {
        faceStatePlatform.mStencilCompareFunction = compareFunction;
        glStencilFuncSeparate(face,
                              compareFunction,
                              rendererState->mStencilCompareReference,
                              rendererState->mStencilCompareMask);
    }

    GLenum stencilTestFailOperation = OpenGLStencilOperation[StencilOperationIndex(faceStateCurrent.mStencilTestFailOperation)];
    GLenum depthTestFailOperation = OpenGLStencilOperation[StencilOperationIndex(faceStateCurrent.mDepthTestFailOperation)];
    GLenum depthTestPassOperation = OpenGLStencilOperation[StencilOperationIndex(faceStateCurrent.mDepthTestPassOperation)];
    if (stencilTestFailOperation != faceStatePlatform.mStencilTestFailOperation
            || depthTestFailOperation != faceStatePlatform.mDepthTestFailOperation
            || depthTestPassOperation != faceStatePlatform.mDepthTestPassOperation)
    {
        faceStatePlatform.mStencilTestFailOperation = stencilTestFailOperation;
        faceStatePlatform.mDepthTestFailOperation = depthTestFailOperation;
        faceStatePlatform.mDepthTestPassOperation = depthTestPassOperation;
        glStencilOpSeparate(face,
                            stencilTestFailOperation,
                            depthTestFailOperation,
                            depthTestPassOperation);
    }
}

void
Renderer::SetStencilTestStatePlatform(const StencilTestState *stencilTestState)
{
    FALCON_ENGINE_CHECK_NULLPTR(stencilTestState);

    mStencilTestStateCurrent = stencilTestState;

    if (mStencilTestStateCurrent->mEnabled)
    {
        if (!mState->mStencilTestEnabled)
        {
            mState->mStencilTestEnabled = true;
            glEnable(GL_STENCIL_TEST);
        }

        if (unsigned int(mStencilTestStateCurrent->mWriteMask) != mState->mStencilWriteMask)
        {
            mState->mStencilWriteMask = unsigned int(mStencilTestStateCurrent->mWriteMask);
            glStencilMask(mStencilTestStateCurrent->mWriteMask);
        }

        bool compareMaskChanged = false;
        if (unsigned int(mStencilTestStateCurrent->mCompareMask) != mState->mStencilCompareMask)
        {
            mState->mStencilCompareMask = unsigned int(mStencilTestStateCurrent->mCompareMask);
            compareMaskChanged = true;
        }

        bool compareReferenceChanged = false;
        if (mStencilTestStateCurrent->mCompareReference != mState->mStencilCompareReference)
        {
            mState->mStencilCompareReference = mStencilTestStateCurrent->mCompareReference;
            compareReferenceChanged = true;
        }

        SetStencilTestFaceStatePlatform(mState.get(),
                                        GL_FRONT,
                                        mStencilTestStateCurrent->mFrontFace,
                                        mState->mStencilFrontFace,
                                        compareMaskChanged,
                                        compareReferenceChanged);

        SetStencilTestFaceStatePlatform(mState.get(),
                                        GL_BACK,
                                        mStencilTestStateCurrent->mBackFace,
                                        mState->mStencilBackFace,
                                        compareMaskChanged,
                                        compareReferenceChanged);
    }
    else if (mState->mStencilTestEnabled)
    {
        mState->mStencilTestEnabled = false;
        glDisable(GL_STENCIL_TEST);
    }
}

void
Renderer::SetWireframeStatePlatform(const WireframeState *wireframeState)
{
    FALCON_ENGINE_CHECK_NULLPTR(wireframeState);

    mWireframeStateCurrent = wireframeState;

    if (mWireframeStateCurrent->mEnabled)
    {
        if (!mState->mWireframeEnabled)
        {
            mState->mWireframeEnabled = true;
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
    }
    else if (mState->mWireframeEnabled)
    {
        mState->mWireframeEnabled = false;
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

/************************************************************************/
/* Viewport Management                                                  */
/************************************************************************/
void
Renderer::SetViewportPlatform(float x, float y, float width, float height, float near, float far)
{
    glViewport(int(x), int(y), int(width), int(height));
    glDepthRange(GLclampd(near), GLclampd(far));
}

/************************************************************************/
/* Default Framebuffer Management                                       */
/************************************************************************/
void
Renderer::ClearColorBufferPlatform(const Vector4f& color)
{
    glClearColor(color[0], color[1], color[2], color[3]);
    glClear(GL_COLOR_BUFFER_BIT);
}

void
Renderer::ClearDepthBufferPlatform(float depth)
{
    glClearDepth(static_cast<GLclampd>(depth));
    glClear(GL_DEPTH_BUFFER_BIT);
}

void
Renderer::ClearFrameBufferPlatform(const Vector4f& color, float depth, unsigned stencil)
{
    glClearColor(color[0], color[1], color[2], color[3]);
    glClearDepth(static_cast<GLclampd>(depth));
    glClearStencil(static_cast<GLint>(stencil));
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void
Renderer::RecoverDeviceLostPlatform()
{
}

void
Renderer::ClearStencilBufferPlatform(unsigned stencil)
{
    glClearStencil(static_cast<GLint>(stencil));
    glClear(GL_STENCIL_BUFFER_BIT);
}

/************************************************************************/
/* Draw                                                                 */
/************************************************************************/
void
Renderer::DrawPrimitivePlatform(const Primitive *primitive, int primitiveInstancingNum)
{
    FALCON_ENGINE_CHECK_NULLPTR(primitive);

    PrimitiveType primitiveType = primitive->GetPrimitiveType();
    const GLenum  primitiveMode = OpenGLPrimitiveType[int(primitiveType)];
    auto vertexNum = primitive->GetVertexNum();
    auto vertexOffset = primitive->GetVertexOffset();

    if (vertexNum < 1)
    {
        return;
    }

    if (primitiveType == PrimitiveType::Point)
    {
        glDrawArraysInstancedBaseInstance(
            primitiveMode, vertexOffset, vertexNum, primitiveInstancingNum, 0);
    }
    else if (primitiveType == PrimitiveType::Line)
    {
        glDrawArraysInstancedBaseInstance(
            primitiveMode, vertexOffset, vertexNum, primitiveInstancingNum, 0);
    }
    else if (primitiveType == PrimitiveType::LineStrip)
    {
        glDrawArraysInstancedBaseInstance(
            primitiveMode, vertexOffset, vertexNum, primitiveInstancingNum, 0);
    }
    else if (primitiveType == PrimitiveType::Triangle)
    {
        // When use index buffer
        auto indexBuffer = primitive->GetIndexBuffer();
        if (indexBuffer)
        {
            auto indexNum = indexBuffer->GetElementNum();
            if (indexNum < 1)
            {
                return;
            }

            auto indexType = indexBuffer->GetIndexType();
            GLenum indexTypeGL = 0;
            const GLvoid *indexOffsetGL = nullptr;
            if (indexType == IndexType::UnsignedShort)
            {
                indexTypeGL = GL_UNSIGNED_SHORT;
                indexOffsetGL = static_cast<unsigned short *>(nullptr)
                                + primitive->GetIndexOffset();
            }
            else if (indexType == IndexType::UnsignedInt)
            {
                indexTypeGL = GL_UNSIGNED_INT;
                indexOffsetGL = static_cast<unsigned int *>(nullptr)
                                + primitive->GetIndexOffset();
            }
            else
            {
                FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
            }

            glDrawElementsInstancedBaseVertexBaseInstance(
                primitiveMode, indexNum, indexTypeGL, indexOffsetGL,
                primitiveInstancingNum, 0, 0);
        }
        else
        {
            glDrawArraysInstancedBaseInstance(
                primitiveMode, vertexOffset, vertexNum, primitiveInstancingNum, 0);
        }
    }
    else
    {
        FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
    }
}

}

#endif