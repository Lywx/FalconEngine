#include <FalconEngine/Context/GameEngineGraphics.h>

#include <FalconEngine/Core/Path.h>
#include <FalconEngine/Context/GameEngineSettings.h>
#include <FalconEngine/Graphics/Renderer/Camera.h>
#include <FalconEngine/Graphics/Renderer/Renderer.h>
#include <FalconEngine/Graphics/Renderer/Entity/EntityRenderer.h>
#include <FalconEngine/Graphics/Renderer/Font/FontRenderer.h>
#include <FalconEngine/Math/Color.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
GameEngineGraphics::GameEngineGraphics() :
    mEntityRenderer(nullptr),
    mFontRenderer(nullptr),
    mMasterRenderer(nullptr)
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
GameEngineGraphics::ClearColorBuffer(Vector4f color)
{
    mMasterRenderer->ClearColorBufferPlatform(color);
}

void
GameEngineGraphics::ClearDepthBuffer(float depth)
{
    mMasterRenderer->ClearDepthBufferPlatform(depth);
}

void
GameEngineGraphics::ClearFrameBuffer(Vector4f color, float depth, unsigned stencil)
{
    mMasterRenderer->ClearFrameBufferPlatform(color, depth, stencil);
}

void
GameEngineGraphics::ClearStencilBuffer(unsigned stencil)
{
    mMasterRenderer->ClearStencilBufferPlatform(stencil);
}

void
GameEngineGraphics::Draw(const Camera *camera, const Entity *entity)
{
    FALCON_ENGINE_CHECK_NULLPTR(entity);

    mEntityRenderer->Draw(camera, entity);
}

void
GameEngineGraphics::DrawBoundingBox(const Camera *camera, const Entity *entity, Color color)
{
    FALCON_ENGINE_CHECK_NULLPTR(entity);

    mEntityRenderer->DrawBoundingBox(camera, entity, color);
}

void
GameEngineGraphics::DrawString(const Font *font, float fontSize, Vector2f textPosition, const std::string& text, Color textColor, float textLineWidth)
{
    FALCON_ENGINE_CHECK_NULLPTR(font);

    mFontRenderer->BatchText(font, fontSize, GetWString(text), textPosition, textColor, textLineWidth);
}

void
GameEngineGraphics::DrawString(const Font *font, float fontSize, Vector2f textPosition, const std::wstring& text, Color textColor, float textLineWidth)
{
    FALCON_ENGINE_CHECK_NULLPTR(font);

    mFontRenderer->BatchText(font, fontSize, text, textPosition, textColor, textLineWidth);
}

const Viewport *
GameEngineGraphics::GetViewport() const
{
    return mMasterRenderer->GetViewport();
}

void
GameEngineGraphics::SetViewport(float x, float y, float width, float height)
{
    mMasterRenderer->SetViewportData(x, y, width, height);
    mMasterRenderer->SetViewportPlatform(x, y, width, height);
}

const Window *
GameEngineGraphics::GetWindow() const
{
    return mMasterRenderer->GetWindow();
}

void
GameEngineGraphics::SetWindow(int width, int height, float near, float far)
{
    mMasterRenderer->SetWindowData(width, height, near, far);
    mMasterRenderer->SetWindowPlatform(width, height, near, far);
}

void
GameEngineGraphics::Initialize(
    _IN_ GameEngineData     *gameEngineData,
    _IN_ GameEngineSettings *gameEngineSettings)
{
    mGameEngineSettings = gameEngineSettings;

    // First initialize primary renderer.
    mMasterRenderer = std::make_shared<Renderer>(gameEngineData, gameEngineSettings);

    // Later initialize sub-renderer.
    mEntityRenderer = std::make_shared<EntityRenderer>();
    mEntityRenderer->Initialize();

    mFontRenderer = std::make_shared<FontRenderer>();
    mFontRenderer->Initialize(mGameEngineSettings->mWindowWidth, mGameEngineSettings->mWindowHeight);
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
    mEntityRenderer->Render(mMasterRenderer.get(), percent);
    mFontRenderer->Render(mMasterRenderer.get(), percent);
}

void
GameEngineGraphics::RenderEnd()
{
    mEntityRenderer->RenderEnd();
    mFontRenderer->RenderEnd();

    // Has to be the last.
    mMasterRenderer->SwapFrameBufferPlatform();
}

}
