#include <FalconEngine/Graphics/Renderer/Renderer.h>

#include <FalconEngine/Graphics/Renderer/PrimitiveLines.h>
#include <FalconEngine/Graphics/Renderer/PrimitivePoints.h>
#include <FalconEngine/Graphics/Renderer/PrimitiveTriangles.h>
#include <FalconEngine/Graphics/Renderer/Scene/Visual.h>
#include <FalconEngine/Graphics/Renderer/Resource/IndexBuffer.h>
#include <FalconEngine/Graphics/Renderer/State/CullState.h>
#include <FalconEngine/Graphics/Renderer/State/OffsetState.h>
#include <FalconEngine/Graphics/Renderer/State/WireframeState.h>

#if defined(FALCON_ENGINE_WINDOW_GLFW)
#include <FalconEngine/Context/Platform/GLFW/GLFWGameEngineData.h>
#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLRendererData.h>
#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLRendererState.h>

using namespace std;

namespace FalconEngine
{

/************************************************************************/
/* Initialization and Destroy                                           */
/************************************************************************/
void
Renderer::InitializePlatform(GameEngineData *gameEngineData)
{
    // Initialize platform renderer data.
    mData = std::unique_ptr<PlatformRendererData, PlatformRendererDataDeleter>(
                new PlatformRendererData(gameEngineData->mWindow), PlatformRendererDataDeleter());
    mData->mState->Initialize(
        mBlendStateDefault.get(),
        mCullStateDefault.get(),
        mDepthTestStateDefault.get(),
        mOffsetStateDefault.get(),
        mStencilTestStateDefault.get(),
        mWireframeStateDefault.get());
    mDataInitialized = true;

    SetWindowPlatform(mWindow.mWidth, mWindow.mHeight, mWindow.mNear, mWindow.mFar);
    SetViewportPlatform(mViewport.mLeft, mViewport.mBottom, mViewport.GetWidth(), mViewport.GetHeight());
}

void
Renderer::DestroyPlatform()
{
}

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
        if (!mData->mState->mBlendEnabled)
        {
            mData->mState->mBlendEnabled = true;
            glEnable(GL_BLEND);
        }

        GLenum sourceFactor = OpenGLBlendFactorSource[int(mBlendStateCurrent->mSourceFactor)];
        GLenum destinationFactor = OpenGLBlendFactorDestination[int(mBlendStateCurrent->mDestinationFactor)];
        if (sourceFactor != mData->mState->mBlendSourceFactor
                || destinationFactor != mData->mState->mBlendDestinationFactor)
        {
            mData->mState->mBlendSourceFactor = sourceFactor;
            mData->mState->mBlendDestinationFactor = destinationFactor;
            glBlendFunc(sourceFactor, destinationFactor);
        }

        if (mBlendStateCurrent->mConstantFactor != mData->mState->mBlendConstantFactor)
        {
            mData->mState->mBlendConstantFactor = mBlendStateCurrent->mConstantFactor;
            glBlendColor(
                mData->mState->mBlendConstantFactor[0],
                mData->mState->mBlendConstantFactor[1],
                mData->mState->mBlendConstantFactor[2],
                mData->mState->mBlendConstantFactor[3]);
        }
    }
    else
    {
        if (mData->mState->mBlendEnabled)
        {
            mData->mState->mBlendEnabled = false;
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
        if (!mData->mState->mCullEnabled)
        {
            mData->mState->mCullEnabled = true;
            glEnable(GL_CULL_FACE);
            glFrontFace(GL_CCW);
            glCullFace(GL_BACK);
        }

        bool cullCounterClockwise = mCullStateCurrent->mCounterClockwise;
        if (cullCounterClockwise != mData->mState->mCullCounterClockwise)
        {
            mData->mState->mCullCounterClockwise = cullCounterClockwise;
            if (mData->mState->mCullCounterClockwise)
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
        if (mData->mState->mCullEnabled)
        {
            mData->mState->mCullEnabled = false;
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
        if (!mData->mState->mDepthTestEnabled)
        {
            mData->mState->mDepthTestEnabled = true;
            glEnable(GL_DEPTH_TEST);
        }

        GLenum compareFunction = OpenGLDepthFunction[int(mDepthTestStateCurrent->mCompareFunction)];
        if (compareFunction != mData->mState->mDepthCompareFunction)
        {
            mData->mState->mDepthCompareFunction = compareFunction;
            glDepthFunc(compareFunction);
        }
    }
    else
    {
        if (mData->mState->mDepthTestEnabled)
        {
            mData->mState->mDepthTestEnabled = false;
            glDisable(GL_DEPTH_TEST);
        }
    }

    if (mDepthTestStateCurrent->mWriteEnabled)
    {
        if (!mData->mState->mDepthWriteEnabled)
        {
            mData->mState->mDepthWriteEnabled = true;
            glDepthMask(GL_TRUE);
        }
    }
    else
    {
        if (mData->mState->mDepthWriteEnabled)
        {
            mData->mState->mDepthWriteEnabled = false;
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
        if (!mData->mState->mOffsetFillEnabled)
        {
            mData->mState->mOffsetFillEnabled = true;
            glEnable(GL_POLYGON_OFFSET_FILL);
        }
    }
    else
    {
        if (mData->mState->mOffsetFillEnabled)
        {
            mData->mState->mOffsetFillEnabled = false;
            glDisable(GL_POLYGON_OFFSET_FILL);
        }
    }

    if (mOffsetStateCurrent->mLineEnabled)
    {
        if (!mData->mState->mOffsetLineEnabled)
        {
            mData->mState->mOffsetLineEnabled = true;
            glEnable(GL_POLYGON_OFFSET_LINE);
        }
    }
    else
    {
        if (mData->mState->mOffsetLineEnabled)
        {
            mData->mState->mOffsetLineEnabled = false;
            glDisable(GL_POLYGON_OFFSET_LINE);
        }
    }

    if (mOffsetStateCurrent->mPointEnabled)
    {
        if (!mData->mState->mOffsetPointEnabled)
        {
            mData->mState->mOffsetPointEnabled = true;
            glEnable(GL_POLYGON_OFFSET_POINT);
        }
    }
    else
    {
        if (mData->mState->mOffsetPointEnabled)
        {
            mData->mState->mOffsetPointEnabled = false;
            glDisable(GL_POLYGON_OFFSET_POINT);
        }
    }

    if (mOffsetStateCurrent->mFactor != mData->mState->mOffsetFactor
            || mOffsetStateCurrent->mUnit != mData->mState->mOffsetUnit)
    {
        mData->mState->mOffsetFactor = mOffsetStateCurrent->mFactor;
        mData->mState->mOffsetUnit = mOffsetStateCurrent->mUnit;
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
        if (!mData->mState->mStencilTestEnabled)
        {
            mData->mState->mStencilTestEnabled = true;
            glEnable(GL_STENCIL_TEST);
        }

        GLenum compareFunction = OpenGLStencilFunction[int(mStencilTestStateCurrent->mCompareFunction)];
        if (compareFunction != mData->mState->mStencilCompareFunction
                || mStencilTestStateCurrent->mCompareReference != mData->mState->mStencilCompareReference
                || mStencilTestStateCurrent->mCompareMask != mData->mState->mStencilCompareMask)
        {
            mData->mState->mStencilCompareFunction = compareFunction;
            mData->mState->mStencilCompareReference = mStencilTestStateCurrent->mCompareReference;
            mData->mState->mStencilCompareMask = mStencilTestStateCurrent->mCompareMask;
            glStencilFunc(compareFunction, mStencilTestStateCurrent->mCompareReference,
                          mStencilTestStateCurrent->mCompareMask);
        }

        if (mStencilTestStateCurrent->mWriteMask != mData->mState->mStencilWriteMask)
        {
            mData->mState->mStencilWriteMask = mStencilTestStateCurrent->mWriteMask;
            glStencilMask(mStencilTestStateCurrent->mWriteMask);
        }

        GLenum onStencilTestFail = OpenGLStencilOperation[int(mStencilTestStateCurrent->OnStencilTestFail)];
        GLenum onDepthTestFail = OpenGLStencilOperation[int(mStencilTestStateCurrent->OnDepthTestFail)];
        GLenum onDepthTestPass = OpenGLStencilOperation[int(mStencilTestStateCurrent->OnDepthTestPass)];
        if (onStencilTestFail != mData->mState->mStencilOnStencilTestFail
                || onDepthTestFail != mData->mState->mStencilOnDepthTestFail
                || onDepthTestPass != mData->mState->mStencilOnDepthTestPass)
        {
            mData->mState->mStencilOnStencilTestFail = onStencilTestFail;
            mData->mState->mStencilOnDepthTestFail = onDepthTestFail;
            mData->mState->mStencilOnDepthTestPass = onDepthTestPass;
            glStencilOp(onStencilTestFail, onDepthTestFail, onDepthTestPass);
        }
    }
    else
    {
        if (mData->mState->mStencilTestEnabled)
        {
            mData->mState->mStencilTestEnabled = false;
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
        if (!mData->mState->mWireframeEnabled)
        {
            mData->mState->mWireframeEnabled = true;
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
    }
    else
    {
        if (mData->mState->mWireframeEnabled)
        {
            mData->mState->mWireframeEnabled = false;
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

void
Renderer::SetWindowPlatform(int width, int height, float near, float far)
{
    if (mDataInitialized)
    {
        glfwSetWindowSize(mData->mWindow, width, height);
        glDepthRange(GLclampd(near), GLclampd(far));
    }
    else
    {
        FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("Renderer data is not initialized.")
    }
}

/************************************************************************/
/* Default Framebuffer Management                                       */
/************************************************************************/
void
Renderer::ClearColorBufferPlatform(Vector4f color)
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
Renderer::ClearFrameBufferPlatform(Vector4f color, float depth, unsigned stencil)
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

void
Renderer::SwapFrameBufferPlatform()
{
    glfwSwapBuffers(mData->mWindow);
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
    if (primitiveType == PrimitiveType::Point)
    {
        auto vertexNum = primitive->GetVertexNum();
        if (vertexNum > 0)
        {
            glDrawArraysInstanced(primitiveMode, 0, GLuint(vertexNum), GLsizei(primitiveInstancingNum));
        }
    }
    else if (primitiveType == PrimitiveType::Line)
    {
        auto vertexNum = primitive->GetVertexNum();
        if (vertexNum > 0)
        {
            glDrawArraysInstanced(primitiveMode, 0, GLuint(vertexNum), GLsizei(primitiveInstancingNum));
        }
    }
    else if (primitiveType == PrimitiveType::LineStrip)
    {
        auto vertexNum = primitive->GetVertexNum();
        if (vertexNum > 0)
        {
            glDrawArraysInstanced(primitiveMode, 0, GLuint(vertexNum), GLsizei(primitiveInstancingNum));
        }
    }
    else if (primitiveType == PrimitiveType::Triangle)
    {
        auto vertexNum = primitive->GetVertexNum();

        // When use index buffer
        auto indexBuffer = primitive->GetIndexBuffer();
        if (indexBuffer)
        {
            auto indexNum = indexBuffer->GetElementNum();
            if (vertexNum > 0 && indexNum > 0)
            {
                GLenum indexType = 0;
                const GLvoid *indexOffset = nullptr;

                if (indexBuffer->mType == IndexType::UnsignedShort)
                {
                    indexType = GL_UNSIGNED_SHORT;
                    indexOffset = static_cast<unsigned short *>(nullptr) + indexBuffer->mOffset;
                }
                else if (indexBuffer->mType == IndexType::UnsignedInt)
                {
                    indexType = GL_UNSIGNED_INT;
                    indexOffset = static_cast<unsigned int *>(nullptr) + indexBuffer->mOffset;
                }
                else
                {
                    FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
                }

                glDrawElementsInstanced(primitiveMode, GLsizei(indexNum), indexType, indexOffset, GLsizei(primitiveInstancingNum));
            }
        }
        else
        {
            glDrawArraysInstanced(primitiveMode, 0, GLuint(vertexNum), GLsizei(primitiveInstancingNum));
        }
    }
    else
    {
        FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
    }
}

}

#endif
