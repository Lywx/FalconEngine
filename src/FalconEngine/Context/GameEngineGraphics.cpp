#include <FalconEngine/Context/GameEngineGraphics.h>

#include <FalconEngine/Core/Path.h>
#include <FalconEngine/Context/GameEngineSettings.h>
#include <FalconEngine/Graphics/Renderer/Camera.h>
#include <FalconEngine/Graphics/Renderer/Renderer.h>
#include <FalconEngine/Graphics/Renderer/Debug/DebugRenderer.h>
#include <FalconEngine/Graphics/Renderer/Entity/EntityRenderer.h>
#include <FalconEngine/Graphics/Renderer/Font/FontRenderer.h>
#include <FalconEngine/Math/Color.h>

#if defined(FALCON_ENGINE_WINDOW_GLFW)
#include <FalconEngine/Context/Platform/GLFW/GLFWGameEngineData.h>
#endif

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
    Destroy();
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
}

void
GameEngineGraphics::Destroy()
{
}

void
GameEngineGraphics::RenderBegin()
{
    mEntityRenderer->RenderBegin();
    mFontRenderer->RenderBegin();
}

void
GameEngineGraphics::Render(double percent)
{
    mEntityRenderer->Render(percent);
    mFontRenderer->Render(percent);
}

void
GameEngineGraphics::RenderEnd()
{
    mEntityRenderer->RenderEnd();
    mFontRenderer->RenderEnd();

    // Has to be the last.
    mMasterRenderer->SwapFrameBufferPlatform();
}

void
GameEngineGraphics::Update(double elapsed)
{
    mDebugRenderer->Update(elapsed);
}

}
