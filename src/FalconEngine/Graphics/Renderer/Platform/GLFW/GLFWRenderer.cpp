#include <FalconEngine/Graphics/Renderer/Renderer.h>
#include <FalconEngine/Context/Platform/GLFW/GLFWGameEngineData.h>

#if defined(FALCON_ENGINE_WINDOW_GLFW)
#include <FalconEngine/Graphics/Renderer/Platform/GLFW/GLFWRendererData.h>
namespace FalconEngine
{

void
Renderer::InitializePlatform()
{
    auto window = GameEngineData::GetInstance()->mWindow;

    // Initialize platform renderer data.
    mData = std::unique_ptr<PlatformRendererData, PlatformRendererDataDeleter>(
                new PlatformRendererData(window),
                PlatformRendererDataDeleter());

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

}

#endif