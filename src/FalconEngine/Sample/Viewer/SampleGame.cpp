#include "SampleGame.h"

using namespace std;

namespace FalconEngine
{
namespace Sample
{

SampleGame::SampleGame():
    mAssetManager(nullptr), mRenderer(nullptr), mFontConsole(nullptr), mFontDisplay(nullptr), mModelAxe(nullptr)
{
}

SampleGame::~SampleGame()
{
    delete mRenderer;
}

void SampleGame::Initialize()
{
    mAssetManager = mAssetManager->GetInstance();

    int width = 1280;
    int height = 800;

    mRenderer = new Renderer("Viewer", width, height);

    mFontConsole = mAssetManager->LoadFont("Content/Fonts/LuciadaConsoleDistanceField.bin");
    mFontDisplay = mAssetManager->LoadFont("Content/Fonts/NSimSunDistanceField.bin");

    mModelAxe = mAssetManager->LoadModel("Content/Models/Axe.obj");
}

void SampleGame::RenderBegin()
{
}

void SampleGame::Render(double percent)
{
    mRenderer->DrawString(100, 100, "", ColorPalette::AliceBlue);
}

void SampleGame::RenderEnd()
{
}

void SampleGame::Update(double elapsed)
{
}

void SampleGame::UpdateInput()
{
}

}
}