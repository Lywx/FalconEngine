#include <FalconEngine/Context/GameEngineGraphics.h>
#include <FalconEngine/Context/GameEngineGraphicsSettings.h>
#include <FalconEngine/Context/GameEngineSettings.h>
#include <FalconEngine/Graphics/Renderers/Renderer.h>
#include <FalconEngine/Graphics/Renderers/BitmapFontRenderer.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
GameEngineGraphics::GameEngineGraphics() :
    mRendererForFont(nullptr),
    mRenderer(nullptr)
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
GameEngineGraphics::DrawStaticString(const BitmapFont *font, float fontSize, Vector2f textPosition, const std::string& text, const Color textColor, float textLineWidth)
{
    mRendererForFont->BatchTextStatic(font, fontSize, text, textPosition, textColor, textLineWidth);
}

void
GameEngineGraphics::DrawString(const BitmapFont *font, float fontSize, Vector2f textPosition, const std::string& text, const Color textColor, float textLineWidth)
{
    mRendererForFont->BatchTextDynamic(font, fontSize, text, textPosition, textColor, textLineWidth);
}

void
GameEngineGraphics::Initialize(
    _IN_  const GameEngineData *data,
    _OUT_ GameEngineSettingsSharedPtr settings)
{
    mSettings = settings->mGraphics;

    {
        if (mRenderer)
        {
            delete mRenderer;
        }

        mRenderer = new Renderer(data, mSettings->mWidth, mSettings->mHeight);
    }

    {
        if (mRendererForFont)
        {
            delete mRendererForFont;
        }

        mRendererForFont = new BitmapFontRenderer();
        mRendererForFont->Initialize(mSettings->mWidth, mSettings->mHeight);
    }

    InitializePlatform(data);
}

void
GameEngineGraphics::Destroy()
{
    delete mRenderer;
    delete mRendererForFont;
}

void
GameEngineGraphics::RenderBegin()
{
    mRendererForFont->RenderBegin();
}

void
GameEngineGraphics::Render(double percent)
{
    mRendererForFont->Render(mRenderer, percent);
}

void
GameEngineGraphics::RenderEnd()
{
    mRendererForFont->RenderEnd();
    mRenderer->SwapBuffers();
}

}
