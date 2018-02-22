#include <FalconEngine/Core/GameEngineGraphics.h>

#include <FalconEngine/Graphics/Renderer/Renderer.h>
#include <FalconEngine/Graphics/Renderer/Debug/DebugRenderer.h>
#include <FalconEngine/Graphics/Renderer/Entity/EntityRenderer.h>
#include <FalconEngine/Graphics/Renderer/Font/FontRenderer.h>
#include <FalconEngine/Graphics/Renderer/Ui/UiRenderer.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
GameEngineGraphics::GameEngineGraphics() :
    mDebugRenderer(nullptr),
    mEntityRenderer(nullptr),
    mFontRenderer(nullptr),
    mMasterRenderer(nullptr),
    mUiRenderer(nullptr)
{
}

GameEngineGraphics::~GameEngineGraphics()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
GameEngineGraphics::Initialize()
{
    // First initialize primary renderer.
    mMasterRenderer = Renderer::GetInstance();
    mMasterRenderer->Initialize();

    // Later initialize sub-renderer.
    mEntityRenderer = EntityRenderer::GetInstance();
    mEntityRenderer->Initialize();

    mFontRenderer = FontRenderer::GetInstance();
    mFontRenderer->Initialize();

    mDebugRenderer = DebugRenderer::GetInstance();
    mDebugRenderer->Initialize();
}

void
GameEngineGraphics::Destroy()
{
    mDebugRenderer->Destroy();
    mEntityRenderer->Destroy();
    mFontRenderer->Destroy();
    mMasterRenderer->Destroy();
    mUiRenderer->Destroy();
}

void
GameEngineGraphics::RenderBegin()
{
    mDebugRenderer->RenderBegin();
    mEntityRenderer->RenderBegin();
    mFontRenderer->RenderBegin();
}

void
GameEngineGraphics::Render(double percent)
{
    mEntityRenderer->Render(percent);

    // NOTE(Wuxiang): The render order is important here.
    mDebugRenderer->Render(percent);
    mFontRenderer->Render(percent);
}

void
GameEngineGraphics::RenderEnd()
{
    mDebugRenderer->RenderEnd();
    mEntityRenderer->RenderEnd();
    mFontRenderer->RenderEnd();

    // Has to be the last.
    mMasterRenderer->SwapFrameBufferPlatform();
}

void
GameEngineGraphics::Update(double /* elapsed */)
{
}

void
GameEngineGraphics::UpdateFrame(double elapsed)
{
    mDebugRenderer->UpdateFrame(elapsed);
}

}
