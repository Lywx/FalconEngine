#include "SampleGame.h"

using namespace std;
using namespace FalconEngine;

SampleGame::SampleGame() :
    mAssetManager(nullptr),
    mFontConsole(nullptr),
    mFontDisplay(nullptr),
    mModelAxe(nullptr)
{
}

SampleGame::~SampleGame()
{
}

void
SampleGame::Initialize()
{
    mAssetManager = mAssetManager->GetInstance();

    int width = 1280;
    int height = 800;

    mFontConsole = mAssetManager->LoadFont("Content/Fonts/LuciadaConsoleDistanceField.fnt.bin");
    mFontDisplay = mAssetManager->LoadFont("Content/Fonts/NSimSunDistanceField.fnt.bin");

    //mModelAxe = mAssetManager->LoadModel("Content/Models/Axe.obj");
}

void
SampleGame::Render(GameEngineGraphics *graphics, double percent)
{
    graphics->DrawString(mFontConsole, 13, Vector2f(100, 100), "Hello", ColorPalette::AliceBlue);

    Game::Render(graphics, percent);
}

void
SampleGame::Update(GameEngineInput *input, double elapsed)
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
