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

    mState->mBlendState.Set(mBlendStateCurrent);
}

void
Renderer::SetCullStatePlatform(const CullState *cullState)
{
    FALCON_ENGINE_CHECK_NULLPTR(cullState);
    mCullStateCurrent = cullState;

    mState->mCullState.Set(mCullStateCurrent);
}

void
Renderer::SetDepthTestStatePlatform(const DepthTestState *depthTestState)
{
    FALCON_ENGINE_CHECK_NULLPTR(depthTestState);
    mDepthTestStateCurrent = depthTestState;

    mState->mDepthTestState.Set(mDepthTestStateCurrent);
}

void
Renderer::SetOffsetStatePlatform(const OffsetState *offsetState)
{
    FALCON_ENGINE_CHECK_NULLPTR(offsetState);
    mOffsetStateCurrent = offsetState;

    mState->mOffsetState.Set(mOffsetStateCurrent);

}

void
Renderer::SetStencilTestStatePlatform(const StencilTestState *stencilTestState)
{
    FALCON_ENGINE_CHECK_NULLPTR(stencilTestState);
    mStencilTestStateCurrent = stencilTestState;

    mState->mStencilTestState.Set(mStencilTestStateCurrent);
}

void
Renderer::SetWireframeStatePlatform(const WireframeState *wireframeState)
{
    FALCON_ENGINE_CHECK_NULLPTR(wireframeState);
    mWireframeStateCurrent = wireframeState;

    mState->mWireframeState.Set(wireframeState);
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