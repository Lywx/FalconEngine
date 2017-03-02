#include "SampleGame.h"

#include <FalconEngine/Context/GameEngineProfiler.h>

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

    mFontConsole = mAssetManager->LoadFont("Content/Fonts/LuciadaConsoleDistanceField.fnt.bin").get();
    mFontDisplay = mAssetManager->LoadFont("Content/Fonts/NSimSunDistanceField.fnt.bin").get();

    //mModelNanosuit = mAssetManager->LoadModel("Content/Models/nanosuit.obj").get();

    mScene = make_shared<Node>();
    mScene->mWorldTransform = Matrix4f::Zero;
    //mScene->AttachChild(mModelNanosuit->GetNode());

    //mScene->Update(0.0, true);
}

void
SampleGame::Render(GameEngineGraphics *graphics, double percent)
{
    graphics->ClearColorBuffer(ColorPalette::White);

    graphics->DrawString(mFontDisplay, 16.f, Vector2f(50.f, 50.f), L"中文支持", ColorPalette::DarkGoldenrod);

    // Draw FPS
    {
        auto engine = GetEngine();
        auto engineGraphicsSettings = GetEngineSettings()->mGraphics;
        auto width  = engineGraphicsSettings->mWidth;
        auto height = engineGraphicsSettings->mHeight;

        auto lastFrameFPS = int(engine->GetProfiler()->GetLastFrameFPS());
        auto lastUpdateElapsedMillisecond = int(engine->GetProfiler()->GetLastUpdateElapsedMillisecond());
        auto lastFrameUpdateCount = int(engine->GetProfiler()->GetLastFrameUpdateTotalCount());
        auto lastRenderElapsedMillisecond = int(engine->GetProfiler()->GetLastRenderElapsedMillisecond());

        graphics->DrawString(mFontConsole, 16.f, Vector2f(50.f, height - 50.f),
                             L"U: " + to_wstring(lastUpdateElapsedMillisecond) + L"ms Uc: " + to_wstring(lastFrameUpdateCount) +
                             L" R: " + to_wstring(lastRenderElapsedMillisecond) + L"ms Rc: " + to_wstring(lastFrameFPS),
                             ColorPalette::DarkGoldenrod);
    }

    //for (int i = 0; i < 100; ++i)
    //{
    //    graphics->DrawString(mFontConsole, 23, Vector2f(0, i + 10), to_string(GameCounter::GetMilliseconds()), ColorPalette::Black);
    //}
    //graphics->DrawString(mFontConsole, 53, Vector2f(300, 300), to_string(GameCounter::GetMilliseconds()), ColorPalette::Black);
    //graphics->Draw(mModelNanosuit->GetNode());
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
