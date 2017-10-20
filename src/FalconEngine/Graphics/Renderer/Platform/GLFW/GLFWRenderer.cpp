#include <FalconEngine/Graphics/Renderer/Renderer.h>

#if defined(FALCON_ENGINE_WINDOW_GLFW)
#include <FalconEngine/Context/GameEngineData.h>
#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLRendererData.h>
#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLRendererState.h>
#include <FalconEngine/Graphics/Renderer/Platform/GLFW/GLFWWindowData.h>
namespace FalconEngine
{

/************************************************************************/
/* Initialization and Destroy                                           */
/************************************************************************/
void
Renderer::InitializePlatform()
{
    InitializeStatePlatform();
    InitializeDataPlatform();

    SetWindowPlatform(mWindow.mWidth, mWindow.mHeight, mWindow.mNear, mWindow.mFar);
    SetViewportPlatform(mViewport.mLeft, mViewport.mBottom, mViewport.GetWidth(), mViewport.GetHeight());
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
Renderer::InitializeDataPlatform()
{
    // Initialize platform renderer data.
    mData = std::unique_ptr<PlatformRendererData, PlatformRendererDataDeleter>(
                new PlatformRendererData(),
                PlatformRendererDataDeleter());
    mData->Initialize(
        GameEngineData::GetInstance()->mWindow);
}

void
Renderer::DestroyPlatform()
{
}

/************************************************************************/
/* Window Management                                                    */
/************************************************************************/
// TODO(Wuxiang):
void
Renderer::SetWindowPlatform(int width, int height, float near, float far)
{
    glfwSetWindowSize(mData->mWindowData->mHandle, width, height);
    glDepthRange(GLclampd(near), GLclampd(far));
}

/************************************************************************/
/* Framebuffer Management                                               */
/************************************************************************/
void
Renderer::SwapFrameBufferPlatform()
{
    glfwSwapBuffers(mData->mWindowData->mHandle);
}

}
#endif