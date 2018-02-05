#include <FalconEngine/Graphics/Renderer/Renderer.h>

#if defined(FALCON_ENGINE_WINDOW_GLFW)
#include <FalconEngine/Core/GameEngineData.h>
#include <FalconEngine/Core/GameEnginePlatform.h>
#include <FalconEngine/Platform/GLFW/GLFWRendererData.h>
#include <FalconEngine/Platform/OpenGL/OpenGLGameEnginePlatformData.h>
#include <FalconEngine/Platform/OpenGL/OpenGLRendererState.h>

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

    SetViewportPlatform(mViewport.mLeft, mViewport.mBottom, mViewport.GetWidth(), mViewport.GetHeight(), mViewport.mNear, mViewport.mFar);
}

void
Renderer::InitializeDataPlatform()
{
    // Initialize platform renderer data.
    mData = std::unique_ptr<PlatformRendererData, PlatformRendererDataDeleter>(
                new PlatformRendererData(GameEnginePlatform::GetInstance()->mWindow->mHandle),
                PlatformRendererDataDeleter());
}

void
Renderer::InitializeStatePlatform()
{
    // Initialize platform renderer state.
    mState = std::unique_ptr<PlatformRendererState, PlatformRendererStateDeleter>(
                 new PlatformRendererState(),
                 PlatformRendererStateDeleter());
    mState->Initialize(
        mBlendStateDefault.get(),
        mCullStateDefault.get(),
        mDepthTestStateDefault.get(),
        mOffsetStateDefault.get(),
        mStencilTestStateDefault.get(),
        mWireframeStateDefault.get());
}

void
Renderer::DestroyPlatform()
{
}

/************************************************************************/
/* Window Management                                                    */
/************************************************************************/
void
Renderer::SetWindowPlatform(int width, int height)
{
    glfwSetWindowSize(mData->mWindowHandle, width, height);
}

/************************************************************************/
/* Framebuffer Management                                               */
/************************************************************************/
void
Renderer::SwapFrameBufferPlatform()
{
    glfwSwapBuffers(mData->mWindowHandle);
}

}
#endif