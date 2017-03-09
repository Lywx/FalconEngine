﻿#include "SampleGame.h"

#include <FalconEngine/Context/GameEngineProfiler.h>
#include <FalconEngine/Graphics/Effects/PhongLightingEffect.h>
#include "FalconEngine/Graphics/Effects/BitmapFontEffect.h"

using namespace std;
using namespace FalconEngine;

SampleGame::SampleGame()
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

    // Initialize Fonts
    mFontConsole = mAssetManager->LoadFont("Content/Fonts/LuciadaConsoleDistanceField.fnt.bin").get();
    // mFontDisplay = mAssetManager->LoadFont("Content/Fonts/NSimSunDistanceField.fnt.bin").get();

    // Initialize Entities
    mCharacter = make_shared<CharacterEntity>(mAssetManager->LoadModel("Content/Models/nanosuit.obj")->GetNode());
    mLamp1 = make_shared<LightEntity>(mAssetManager->LoadModel("Content/Models/Lamp.obj")->GetNode());
    mLamp2 = make_shared<LightEntity>(mAssetManager->LoadModel("Content/Models/Lamp.obj")->GetNode());

    mScenePointLightList.push_back(mLamp1->mLight.get());
    mScenePointLightList.push_back(mLamp2->mLight.get());

    //mLamp1->GetNode()->mWorldTransform =
    // mLamp1->mLight.mPosition

    // Initialize Scene
    mScene = make_shared<Node>();
    mScene->mWorldTransform = Matrix4f::Zero;
    mScene->AttachChild(mCharacter->GetNode());

    //
    mSceneLightingEffect = make_shared<PhongLightingEffect>();
    mSceneDirectionalLight = make_shared<Light>(LightType::Directional);
    mSceneDirectionalLight->mAmbient = Color(255, 255, 255);
    mSceneDirectionalLight->mDiffuse = Color(255, 255, 255);
    mSceneDirectionalLight->mSpecular = Color(255, 255, 255);
    mSceneDirectionalLight->mDirection = Vector3f(1, 1, 1);

    // Initialize Effect
    mSceneLightingEffect->CreateInstance(mSceneLightingEffect, mCharacter->GetNode().get(), mSceneDirectionalLight.get(), mScenePointLightList, mSceneSpotLightList);

    mCamera->LookAt(Vector3f(0, 0, 10), Vector3f(0, 0, 0), Vector3f::UnitY);
}

void
SampleGame::Render(GameEngineGraphics *graphics, double percent)
{
    graphics->ClearBuffers(ColorPalette::Black, 1.f, 0);

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

        graphics->DrawString(mFontConsole, 16.f, Vector2f(50.f, 10 * 50 + 100.f),
                             "01234567890", ColorPalette::DarkRed);
    }

    graphics->Draw(mCamera.get(), mCharacter.get());
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

    mCamera->Update(input, elapsed);
    mScene->Update(elapsed, true);

    Game::Update(input, elapsed);
}
