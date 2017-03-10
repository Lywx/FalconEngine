#include "SampleGame.h"

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
    // Initialize debug context.
    GameDebug::Initialize();

    // Load all assets.
    {
        auto assetManager = AssetManager::GetInstance();

        // Fonts
        {
            mFont_Console = assetManager->LoadFont("Content/Fonts/LuciadaConsoleDistanceField.fnt.bin").get();
            // mFontDisplay = mAssetManager->LoadFont("Content/Fonts/NSimSunDistanceField.fnt.bin").get();
        }

        // Entities
        {
            // mCharacter = make_shared<CharacterEntity>(assetManager->LoadModel("Content/Models/nanosuit.obj")->GetNode());
            mRoom = make_shared<SceneEntity>(assetManager->LoadModel("Content/Models/Bedroom.dae")->GetNode());
        }
    }

    {
        {
            mDirectionalLight = make_shared<Light>(LightType::Directional);
            mDirectionalLight->mAmbient = Color(055, 055, 055);
            //mDirectionalLight->mDiffuse = Color(055, 255, 255);
            //mDirectionalLight->mSpecular = Color(255, 255, 255);
            //mDirectionalLight->mDirection = Vector3f(1, 1, 1);
        }

        {
            mPointLight1 = make_shared<Light>(LightType::Point);
            mPointLight1->mAmbient = Color(255, 255, 255);
            mPointLight1->mDiffuse = Color(255, 255, 255);
            mPointLight1->mSpecular = Color(255, 255, 255);
            mPointLight1->mConstant = 0.1;
            mPointLight1->mLinear = 0.7;
            mPointLight1->mQuadratic = 1.8;
            mPointLight1->mPosition = Vector3f(4.9f, 4.5f, 6.5f);
            //mPointLight1->mPosition = Vector3f(5.09701681137085, -6.6115264892578125, 2.654505729675293);
        }

        {
            mPointLight2 = make_shared<Light>(LightType::Point);
            mPointLight2->mAmbient = Color(255, 255, 255);
            mPointLight2->mDiffuse = Color(255, 255, 255);
            mPointLight2->mSpecular = Color(255, 255, 255);
            mPointLight2->mDirection = Vector3f(1, 1, 1);
            mPointLight2->mConstant = 1.0;
            mPointLight2->mLinear = 0.7;
            mPointLight2->mQuadratic = 1.8;
            mPointLight2->mPosition = Vector3f(-4.92804479598999, -6.6115264892578125, 2.654505729675293);
        }

        // Initialize Scene
        mScenePointLightList = { mPointLight1.get(), mPointLight2.get() };

        mSceneNode = make_shared<Node>();
        mSceneNode->mWorldTransform = Matrix4f::Zero;
        mSceneNode->AttachChild(mRoom->GetNode());

        //
        mSceneLightingEffect = make_shared<PhongLightingEffect>();

        // Initialize Effect
        mSceneLightingEffect->CreateInstance(mSceneLightingEffect, mRoom->GetNode().get(), *mDirectionalLight, mScenePointLightList, mSceneSpotLightList);
    }

    // Initialize interaction.
    {
        mCamera->LookAt(Vector3f(0, 0, 0), Vector3f(0, 0, -1), Vector3f::UnitY);
    }
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

        graphics->DrawString(mFont_Console, 16.f, Vector2f(50.f, height - 50.f),
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

        graphics->DrawString(mFont_Console, 16.f, Vector2f(50.f, height - 100.f),
                             "Mouse Position: " + to_string(mousePosition) + " Diff: " + to_string(mousePositionDiff), ColorPalette::DarkRed);
    }

    // Draw Camera
    {
        auto position = mCamera->GetPosition();
        graphics->DrawString(mFont_Console, 16.f, Vector2f(50.f, 50.f),
                             "Camera Position: " + to_string(position), ColorPalette::DarkRed);

        auto pitch = Degree(mCamera->mPitch);
        auto yaw = Degree(mCamera->mYaw);
        auto roll = Degree(mCamera->mRoll);
        graphics->DrawString(mFont_Console, 16.f, Vector2f(50.f, 100.f),
                             "Camera Pitch: " + std::to_string(pitch) + " Yaw: " + std::to_string(yaw) + " Roll: " + std::to_string(roll), ColorPalette::DarkRed);
    }

    graphics->Draw(mCamera.get(), mRoom.get());
    graphics->DrawBoundingBox(mCamera.get(), mRoom.get(), ColorPalette::Yellow);

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
    mSceneNode->Update(elapsed, true);

    Game::Update(input, elapsed);
}
