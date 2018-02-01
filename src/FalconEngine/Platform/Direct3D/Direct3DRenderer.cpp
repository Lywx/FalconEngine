#include <FalconEngine/Graphics/Renderer/Renderer.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Core/Exception.h>
#include <FalconEngine/Core/GameEnginePlatform.h>
#include <FalconEngine/Platform/Direct3D/Direct3DGameEnginePlatformData.h>
#include <FalconEngine/Platform/Direct3D/Direct3DRendererData.h>
#include <FalconEngine/Platform/Direct3D/Direct3DRendererState.h>

namespace FalconEngine
{

/************************************************************************/
/* Initialization and Destroy                                           */
/************************************************************************/
void
Renderer::InitializePlatform()
{
    InitializeDataPlatform();
    InitializeStatePlatform();
}

void
Renderer::InitializeDataPlatform()
{
    // Initialize platform renderer data.
    mData = std::unique_ptr<PlatformRendererData, PlatformRendererDataDeleter>(
            new PlatformRendererData(),
            PlatformRendererDataDeleter());

    // NOTE(Wuxiang): Because the Direct3D device might be lost during running.
    GameEnginePlatform::GetInstance()->mData->mContext.AsWeak(&mData->mContext);
    GameEnginePlatform::GetInstance()->mData->mDevice.AsWeak(&mData->mDevice);

    FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
}

void
Renderer::InitializeStatePlatform()
{
    FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
}

void
Renderer::DestroyPlatform()
{
    FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
}

/************************************************************************/
/* State Management                                                     */
/************************************************************************/
void
Renderer::SetBlendStatePlatform(const BlendState *blendState)
{
    FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
}

void
Renderer::SetCullStatePlatform(const CullState *cullState)
{
    FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
}

void
Renderer::SetDepthTestStatePlatform(const DepthTestState *depthTestState)
{
    FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
}

void
Renderer::SetOffsetStatePlatform(const OffsetState *offsetState)
{
    FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
}

void
Renderer::SetStencilTestStatePlatform(const StencilTestState *stencilTestState)
{
    FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
}

void
Renderer::SetWireframeStatePlatform(const WireframeState *wireframeState)
{
    FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
}

/************************************************************************/
/* Viewport Management                                                  */
/************************************************************************/
void
Renderer::SetViewportPlatform(float x, float y, float width, float height)
{
    FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
}

/************************************************************************/
/* Window Management                                                    */
/************************************************************************/
void
Renderer::SetWindowPlatform(int width, int height, float near, float far)
{
    FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
}

/************************************************************************/
/* Framebuffer Management                                               */
/************************************************************************/
void
Renderer::ClearColorBufferPlatform(const Vector4f& color)
{
    FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
}

void
Renderer::ClearDepthBufferPlatform(float depth)
{
    FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
}

void
Renderer::ClearStencilBufferPlatform(unsigned stencil)
{
    FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
}

void
Renderer::ClearFrameBufferPlatform(const Vector4f& color, float depth, unsigned stencil)
{
    FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
}

void
Renderer::SwapFrameBufferPlatform()
{
    FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
}

void
Renderer::DrawPrimitivePlatform(const Primitive *primitive, int instancingNum)
{
    FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
}

}

#endif