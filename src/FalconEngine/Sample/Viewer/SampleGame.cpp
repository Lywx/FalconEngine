#include "SampleGame.h"

using namespace std;
using namespace FalconEngine;

SampleGame::SampleGame() :
    mAssetManager(nullptr),
    mFontConsole(nullptr),
    mFontDisplay(nullptr),
    mModelNanosuit(nullptr)
{
}

SampleGame::~SampleGame()
{
}

GameEngineSettingsSharedPtr
SampleGame::GetEngineSettings()
{
    if (!mGameEngineSettings)
    {
        mGameEngineSettings = std::make_shared<GameEngineSettings>();
        mGameEngineSettings->mGraphics->mWidth  = 1600;
        mGameEngineSettings->mGraphics->mHeight = 900;
    }

    return mGameEngineSettings;
}

void
SampleGame::Initialize()
{
    GameDebug::Initialize();
    mAssetManager = mAssetManager->GetInstance();

    int width = 1280;
    int height = 800;

    mFontConsole = mAssetManager->LoadFont("Content/Fonts/LuciadaConsoleDistanceField.fnt.bin").get();
    //mFontDisplay = mAssetManager->LoadFont("Content/Fonts/NSimSunDistanceField.fnt.bin");

    mModelNanosuit = mAssetManager->LoadModel("Content/Models/nanosuit.obj").get();

    mScene = make_shared<Node>();
    mScene->mWorldTransform = Matrix4f::Zero;
    mScene->AttachChild(mModelNanosuit->GetNode());

    mScene->Update(0.0, true);
}

void
SampleGame::Render(GameEngineGraphics *graphics, double percent)
{
    graphics->ClearColorBuffer(ColorPalette::White);

    graphics->DrawString(mFontConsole, 53, Vector2f(300, 300), to_string(GameCounter::GetMilliseconds()), ColorPalette::Black);
    graphics->Draw(mModelNanosuit->GetNode());
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

    mScene->Update(elapsed, true);
}
