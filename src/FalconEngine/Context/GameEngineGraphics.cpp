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
}


/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
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
}

}
