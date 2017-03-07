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
    mCamera = make_shared<FirstPersonCamera>(&mHandedness);
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
    mCamera->LookAt(Vector3f(0, 0, 10), Vector3f(0, 0, 0), Vector3f::UnitY);
}

void
SampleGame::Render(GameEngineGraphics *graphics, double percent)
{
    graphics->ClearBuffers(ColorPalette::Black, 1.f, 0.0f);

    auto engine = GetEngine();
    auto engineGraphicsSettings = GetEngineSettings()->mGraphics;
    auto width  = engineGraphicsSettings->mWidth;
    auto height = engineGraphicsSettings->mHeight;

    // Draw Profiler
    {
        auto profiler = GameEngineProfiler::GetInstance();
        auto lastFrameFPS = int(profiler->GetLastFrameFPS());
        auto lastUpdateElapsedMillisecond = int(profiler->GetLastUpdateElapsedMillisecond());
        auto lastFrameUpdateCount = int(profiler->GetLastFrameUpdateTotalCount());
        auto lastRenderElapsedMillisecond = int(profiler->GetLastRenderElapsedMillisecond());

        graphics->DrawString(mFontConsole, 16.f, Vector2f(50.f, height - 50.f),
                             "U: " + std::to_string(lastUpdateElapsedMillisecond) + "ms Uc: " + std::to_string(lastFrameUpdateCount) +
                             " R: " + std::to_string(lastRenderElapsedMillisecond) + "ms Rc: " + std::to_string(lastFrameFPS),
                             ColorPalette::DarkGoldenrod);
    }

    auto input = GameEngineInput::GetInstance();
    auto keyboard = input->GetKeyboardState();
    auto mouse = input->GetMouseState();

    // Draw Mouse
    {
        auto mousePositionDiff = mouse->GetPositionDiff();
        auto mousePosition = mouse->GetPosition();

        graphics->DrawString(mFontConsole, 16.f, Vector2f(50.f, height - 100.f),
                             "Mouse Postion: " + to_string(mousePosition) + " Diff: " + to_string(mousePositionDiff), ColorPalette::DarkRed);
    }

    // Draw Camera
    {
        auto position = mCamera->GetPosition();
        graphics->DrawString(mFontConsole, 16.f, Vector2f(50.f, 50.f),
                             "Camera Position: " + to_string(position), ColorPalette::DarkRed);

        auto pitch = Degree(mCamera->mPitch);
        auto yaw = Degree(mCamera->mYaw);
        auto roll = Degree(mCamera->mRoll);
        graphics->DrawString(mFontConsole, 16.f, Vector2f(50.f, 100.f),
                             "Camera Pitch: " + std::to_string(pitch) + " Yaw: " + std::to_string(yaw) + " Roll: " + std::to_string(roll), ColorPalette::DarkRed);

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

    auto engine = GetEngine();
    auto engineGraphicsSettings = GetEngineSettings()->mGraphics;
    auto width  = engineGraphicsSettings->mWidth;
    auto height = engineGraphicsSettings->mHeight;
    auto speed = engine->GetMillisecondPerRender();

    auto sensitivity = 1.000;
    auto cameralooksmoothing = 2.0;
    auto cameraypositionsmoothing = 3.0;
    auto smoothedcamerapositiony = 0;

    auto mousePositionCenter = Vector2f(width / 2, height / 2);
    auto mousePosition = mouse->GetPosition();
    auto mousePositionOffset = mouse->GetPositionDiff();
    //if (mousePositionOffset == Vector2f::Zero)
    //{
    //    GameDebug::Break();
    //}

    auto b = Vector2f(mousePositionOffset.x / width,
                      mousePositionOffset.y / height);

    // auto mouseController = input->GetMouseController();
    // mouseController->SetPosition(mousePositionCenter);

    //auto mousespeed = Vector2f();
    //mousespeed.x = Math::Curve(mousePositionOffset.x, mousespeed.x, cameralooksmoothing / elapsed);
    //mousespeed.y = Math::Curve(mousePositionOffset.y, mousespeed.y, cameralooksmoothing / elapsed);

    auto pitch = mCamera->mPitch;
    auto pitchDegree = Degree(pitch);
    pitchDegree = Clamp<float>(pitchDegree + mousePositionOffset.y * sensitivity * elapsed / speed, 0, 180);
    mCamera->mPitch = Radian(pitchDegree);

    auto yaw = mCamera->mYaw;
    auto yawDegree = Degree(yaw);
    yawDegree = Clamp<float>(yawDegree - mousePositionOffset.x * sensitivity * elapsed / speed, -180, 180);
    mCamera->mYaw = Radian(yawDegree);

    //mCamera->SetRotation(mousePositionOffset.y, mousePositionOffset.x, 0);
    auto f = elapsed / speed;
    if (keyboard->KeyPressed(Key::S))
    {
        mCamera->MoveBackward(1 * f);
    }

    if (keyboard->KeyPressed(Key::W))
    {
        mCamera->MoveForward(1 * f);
    }

    if (keyboard->KeyPressed(Key::A))
    {
        mCamera->MoveLeft(1 * f);
    }

    if (keyboard->KeyPressed(Key::D))
    {
        mCamera->MoveRight(1 * f);
    }

    mCamera->Update(elapsed);
    mScene->Update(elapsed, true);
}
