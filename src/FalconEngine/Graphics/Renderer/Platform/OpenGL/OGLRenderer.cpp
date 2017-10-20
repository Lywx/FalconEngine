#include <FalconEngine/Graphics/Renderer/Renderer.h>

#include <FalconEngine/Graphics/Renderer/PrimitiveLines.h>
#include <FalconEngine/Graphics/Renderer/PrimitivePoints.h>
#include <FalconEngine/Graphics/Renderer/PrimitiveTriangles.h>
#include <FalconEngine/Graphics/Renderer/Scene/Visual.h>
#include <FalconEngine/Graphics/Renderer/Resource/IndexBuffer.h>
#include <FalconEngine/Graphics/Renderer/State/CullState.h>
#include <FalconEngine/Graphics/Renderer/State/OffsetState.h>
#include <FalconEngine/Graphics/Renderer/State/WireframeState.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLRendererData.h>
#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLRendererState.h>
#endif

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

        GLenum sourceFactor = OpenGLBlendFactorSource[int(mBlendStateCurrent->mSourceFactor)];
        GLenum destinationFactor = OpenGLBlendFactorDestination[int(mBlendStateCurrent->mDestinationFactor)];
        if (sourceFactor != mState->mBlendSourceFactor
                || destinationFactor != mState->mBlendDestinationFactor)
        {
            mState->mBlendSourceFactor = sourceFactor;
            mState->mBlendDestinationFactor = destinationFactor;
            glBlendFunc(sourceFactor, destinationFactor);
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
    }
    else
    {
        if (mState->mBlendEnabled)
        {
            mState->mBlendEnabled = false;
            glDisable(GL_BLEND);
        }
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
    else
    {
        if (mState->mCullEnabled)
        {
            mState->mCullEnabled = false;
            glDisable(GL_CULL_FACE);
        }
    }
}

void
Renderer::SetDepthTestStatePlatform(const DepthTestState *depthTestState)
{
    FALCON_ENGINE_CHECK_NULLPTR(depthTestState);

    mDepthTestStateCurrent = depthTestState;

    if (mDepthTestStateCurrent->mTestEnabled)
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
    else
    {
        if (mState->mDepthTestEnabled)
        {
            mState->mDepthTestEnabled = false;
            glDisable(GL_DEPTH_TEST);
        }
    }

    if (mDepthTestStateCurrent->mWriteEnabled)
    {
        if (!mState->mDepthWriteEnabled)
        {
            mState->mDepthWriteEnabled = true;
            glDepthMask(GL_TRUE);
        }
    }
    else
    {
        if (mState->mDepthWriteEnabled)
        {
            mState->mDepthWriteEnabled = false;
            glDepthMask(GL_FALSE);
        }
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
    else
    {
        if (mState->mOffsetFillEnabled)
        {
            mState->mOffsetFillEnabled = false;
            glDisable(GL_POLYGON_OFFSET_FILL);
        }
    }

    if (mOffsetStateCurrent->mLineEnabled)
    {
        if (!mState->mOffsetLineEnabled)
        {
            mState->mOffsetLineEnabled = true;
            glEnable(GL_POLYGON_OFFSET_LINE);
        }
    }
    else
    {
        if (mState->mOffsetLineEnabled)
        {
            mState->mOffsetLineEnabled = false;
            glDisable(GL_POLYGON_OFFSET_LINE);
        }
    }

    if (mOffsetStateCurrent->mPointEnabled)
    {
        if (!mState->mOffsetPointEnabled)
        {
            mState->mOffsetPointEnabled = true;
            glEnable(GL_POLYGON_OFFSET_POINT);
        }
    }
    else
    {
        if (mState->mOffsetPointEnabled)
        {
            mState->mOffsetPointEnabled = false;
            glDisable(GL_POLYGON_OFFSET_POINT);
        }
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
Renderer::SetStencilTestStatePlatform(const StencilTestState *stencilTestState)
{
    FALCON_ENGINE_CHECK_NULLPTR(stencilTestState);

    mStencilTestStateCurrent = stencilTestState;

    if (mStencilTestStateCurrent->mTestEnabled)
    {
        if (!mState->mStencilTestEnabled)
        {
            mState->mStencilTestEnabled = true;
            glEnable(GL_STENCIL_TEST);
        }

        GLenum compareFunction = OpenGLStencilFunction[int(mStencilTestStateCurrent->mCompareFunction)];
        if (compareFunction != mState->mStencilCompareFunction
                || mStencilTestStateCurrent->mCompareReference != mState->mStencilCompareReference
                || mStencilTestStateCurrent->mCompareMask != mState->mStencilCompareMask)
        {
            mState->mStencilCompareFunction = compareFunction;
            mState->mStencilCompareReference = mStencilTestStateCurrent->mCompareReference;
            mState->mStencilCompareMask = mStencilTestStateCurrent->mCompareMask;
            glStencilFunc(compareFunction, mStencilTestStateCurrent->mCompareReference,
                          mStencilTestStateCurrent->mCompareMask);
        }

        if (mStencilTestStateCurrent->mWriteMask != mState->mStencilWriteMask)
        {
            mState->mStencilWriteMask = mStencilTestStateCurrent->mWriteMask;
            glStencilMask(mStencilTestStateCurrent->mWriteMask);
        }

        GLenum onStencilTestFail = OpenGLStencilOperation[int(mStencilTestStateCurrent->OnStencilTestFail)];
        GLenum onDepthTestFail = OpenGLStencilOperation[int(mStencilTestStateCurrent->OnDepthTestFail)];
        GLenum onDepthTestPass = OpenGLStencilOperation[int(mStencilTestStateCurrent->OnDepthTestPass)];
        if (onStencilTestFail != mState->mStencilOnStencilTestFail
                || onDepthTestFail != mState->mStencilOnDepthTestFail
                || onDepthTestPass != mState->mStencilOnDepthTestPass)
        {
            mState->mStencilOnStencilTestFail = onStencilTestFail;
            mState->mStencilOnDepthTestFail = onDepthTestFail;
            mState->mStencilOnDepthTestPass = onDepthTestPass;
            glStencilOp(onStencilTestFail, onDepthTestFail, onDepthTestPass);
        }
    }
    else
    {
        if (mState->mStencilTestEnabled)
        {
            mState->mStencilTestEnabled = false;
            glDisable(GL_STENCIL_TEST);
        }
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
    else
    {
        if (mState->mWireframeEnabled)
        {
            mState->mWireframeEnabled = false;
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
    }
}

/************************************************************************/
/* Viewport Management                                                  */
/************************************************************************/
void
Renderer::SetViewportPlatform(float x, float y, float width, float height)
{
    glViewport(int(x), int(y), int(width), int(height));
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
        glDrawArraysInstanced(primitiveMode, vertexOffset, vertexNum, primitiveInstancingNum);
    }
    else if (primitiveType == PrimitiveType::Line)
    {
        glDrawArraysInstanced(primitiveMode, vertexOffset, vertexNum, primitiveInstancingNum);
    }
    else if (primitiveType == PrimitiveType::LineStrip)
    {
        glDrawArraysInstanced(primitiveMode, vertexOffset, vertexNum, primitiveInstancingNum);
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

            GLenum indexType = 0;
            const GLvoid *indexOffset = nullptr;

            if (indexBuffer->GetIndexType() == IndexType::UnsignedShort)
            {
                indexType = GL_UNSIGNED_SHORT;
                indexOffset = static_cast<unsigned short *>(nullptr) + primitive->GetIndexOffset();
            }
            else if (indexBuffer->GetIndexType() == IndexType::UnsignedInt)
            {
                indexType = GL_UNSIGNED_INT;
                indexOffset = static_cast<unsigned int *>(nullptr) + primitive->GetIndexOffset();
            }
            else
            {
                FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
            }

            glDrawElementsInstanced(primitiveMode, indexNum, indexType, indexOffset, primitiveInstancingNum);
        }
        else
        {
            glDrawArraysInstanced(primitiveMode, vertexOffset, vertexNum, primitiveInstancingNum);
        }
    }
    else
    {
        FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
    }
}

}