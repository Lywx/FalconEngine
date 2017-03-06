#include "SampleGame.h"

#include <FalconEngine/Context/GameEngineProfiler.h>
#include <FalconEngine/Graphics/Effects/PhongLightingEffect.h>

using namespace std;
using namespace FalconEngine;

SampleGame::SampleGame() :
    mAssetManager(nullptr),
    mFontConsole(nullptr),
    mFontDisplay(nullptr),
    mModelNanosuit(nullptr)
{
    mCamera = make_shared<Camera>(&mHandedness);
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

    mModelNanosuit = mAssetManager->LoadModel("Content/Models/nanosuit.obj").get();
    mModelPerson = make_shared<Character>(mModelNanosuit->GetNode());

    auto phongLightingEffect = make_shared<PhongLightingEffect>();
    auto a = make_shared<VisualEffectInstance>(phongLightingEffect);
    auto b = make_shared<Light>(LightType::Directional);
    b->mDirection = Vector3f(1, 1, 1);
    b->mAmbient = Color(255, 255, 255);
    b->mDiffuse = Color(255, 255, 255);
    b->mSpecular = Color(255, 255, 255);

    phongLightingEffect->CreateInstance(phongLightingEffect, mModelPerson->GetNode().get(), b.get());

    mScene = make_shared<Node>();
    mScene->mWorldTransform = Matrix4f::Zero;
    mScene->AttachChild(mModelPerson->GetNode());
    mScene->Update(0.0, true);
}

void
SampleGame::Render(GameEngineGraphics *graphics, double percent)
{
    graphics->ClearColorBuffer(ColorPalette::Black);

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
                             "U: " + std::to_string(lastUpdateElapsedMillisecond) + "ms Uc: " + std::to_string(lastFrameUpdateCount) +
                             " R: " + std::to_string(lastRenderElapsedMillisecond) + "ms Rc: " + std::to_string(lastFrameFPS),
                             ColorPalette::DarkGoldenrod);
    }

    {
        auto position = mCamera->GetPosition();
        graphics->DrawString(mFontConsole, 16.f, Vector2f(50.f, 50.f),
                             "P: " + to_string(position), ColorPalette::DarkRed);

    }

    graphics->Draw(mCamera.get(), mModelPerson.get());
    //graphics->DrawBoundingBox(mCamera.get(), mModelPerson.get(), ColorPalette::Red);

    Game::Render(graphics, percent);
}

void
SampleGame::Update(GameEngineInput *input, double elapsed)
{
    auto keyboard = input->GetKeyboardState();
    auto mouse = input->GetMouseState();

    if (keyboard->KeyPressed(Key::Escape))
    {
        GetEngine()->Exit();
    }

    auto diff = mouse->GetPositionDiff();
    mCamera->SetRotation(diff.x, diff.y, 0);

    if (keyboard->KeyPressed(Key::S))
    {
        mCamera->MoveBackward(1 * elapsed);
    }

    if (keyboard->KeyPressed(Key::W))
    {
        mCamera->MoveForward(1 * elapsed);
    }

    if (keyboard->KeyPressed(Key::A))
    {
        mCamera->MoveLeft(1 * elapsed);
    }

    if (keyboard->KeyPressed(Key::D))
    {
        mCamera->MoveRight(1 * elapsed);
    }

    mCamera->Update(elapsed);
    mScene->Update(elapsed, true);
}
