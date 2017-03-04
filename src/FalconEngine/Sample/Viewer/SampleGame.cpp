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
    // mFontDisplay = mAssetManager->LoadFont("Content/Fonts/NSimSunDistanceField.fnt.bin").get();

    //mModelNanosuit = mAssetManager->LoadModel("Content/Models/nanosuit.obj").get();

    //mScene = make_shared<Node>();
    //mScene->mWorldTransform = Matrix4f::Zero;
    //mScene->AttachChild(mModelNanosuit->GetNode());
    //mScene->Update(0.0, true);
}

void
SampleGame::Render(GameEngineGraphics *graphics, double percent)
{
    graphics->ClearColorBuffer(ColorPalette::White);

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
                             "U: " + to_string(lastUpdateElapsedMillisecond) + "ms Uc: " + to_string(lastFrameUpdateCount) +
                             " R: " + to_string(lastRenderElapsedMillisecond) + "ms Rc: " + to_string(lastFrameFPS),
                             ColorPalette::DarkGoldenrod);
    }

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

    //mScene->Update(elapsed, true);
}
