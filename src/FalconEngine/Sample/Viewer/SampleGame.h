#pragma once

#include <FalconEngine/Content.h>
#include <FalconEngine/Context.h>
#include <FalconEngine/Core.h>
#include <FalconEngine/Graphics.h>
#include <FalconEngine/Math.h>

namespace FalconEngine
{
namespace Sample
{

class SampleGame : public Game
{
public:
    SampleGame();
    ~SampleGame();

    virtual void
    Initialize() override;

    virtual void
    RenderBegin() override;

    virtual void
    Render(double percent) override;

    virtual void
    RenderEnd() override;

    virtual void
    Update(double elapsed) override;

    virtual void
    UpdateInput() override;

private:
    AssetManager *mAssetManager;
    GameEngineGraphics *mRenderer;

    const BitmapFont *mFontConsole;
    const BitmapFont *mFontDisplay;

    Model *mModelAxe;
};

}
}
