#include <FalconEngine/Context/GameEngineGraphics.h>
#include <FalconEngine/Context/GameEngineGraphicsSettings.h>
#include <FalconEngine/Context/GameEngineSettings.h>
#include <FalconEngine/Graphics/Renderer/Renderer.h>
#include <FalconEngine/Graphics/Renderer/Font/BitmapFontRenderer.h>
#include <FalconEngine/Math/Color.h>

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
GameEngineGraphics::ClearColorBuffer(Vector4f color)
{
    mRenderer->ClearColorBuffer(color);
}

void
GameEngineGraphics::ClearDepthBuffer(float depth)
{
    mRenderer->ClearDepthBuffer(depth);
}

void
GameEngineGraphics::ClearStencilBuffer(unsigned stencil)
{
    mRenderer->ClearStencilBuffer(stencil);
}

void
GameEngineGraphics::ClearBuffers(Vector4f color, float depth, unsigned stencil)
{
    mRenderer->ClearBuffers(color, depth, stencil);
}

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
