#include "SampleGame.h"

using namespace std;
using namespace FalconEngine;

SampleGame::SampleGame() :
    mAssetManager(nullptr), mRenderer(nullptr), mFontConsole(nullptr), mFontDisplay(nullptr), mModelAxe(nullptr)
{
}

SampleGame::~SampleGame()
{
    delete mRenderer;
}

void
SampleGame::Initialize()
{
    mAssetManager = mAssetManager->GetInstance();

    int width = 1280;
    int height = 800;

    mFontConsole = mAssetManager->LoadFont("Content/Fonts/LuciadaConsoleDistanceField.fnt.bin");
    mFontDisplay = mAssetManager->LoadFont("Content/Fonts/NSimSunDistanceField.fnt.bin");

    mModelAxe = mAssetManager->LoadModel("Content/Models/Axe.obj");
}

void
SampleGame::RenderBegin()
{
}

void
SampleGame::Render(double percent)
{
    mRenderer->DrawString(100, 100, "", ColorPalette::AliceBlue);
}

void
SampleGame::RenderEnd()
{
}

void
SampleGame::Update(const GameEngineInput *input, double elapsed)
{
    auto keyboard = input->GetKeyboardState();
    if (keyboard->KeyPressed(Key::Escape))
    {
        GetEngine()->Exit();
    }

    auto mouse = input->GetMouseState();
    if (mouse->ButtonDown(MouseButton::LeftButton))
    {
        GetEngine()->Exit();
    }
}
