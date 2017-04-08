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
            auto model = assetManager->LoadModel("Content/Models/Bedroom.dae");
            mRoom = make_shared<SceneEntity>(shared_ptr<Node>(model->GetNode()->GetClone()));

            model = assetManager->LoadModel("Content/Models/Engine/Point Light.dae");
            mPointLight1 = make_shared<PointLightEntity>(shared_ptr<Node>(model->GetNode()->GetClone()));
            mPointLight2 = make_shared<PointLightEntity>(shared_ptr<Node>(model->GetNode()->GetClone()));
            mPointLight3 = make_shared<PointLightEntity>(shared_ptr<Node>(model->GetNode()->GetClone()));
        }
    }

    // Initialize Scene
    {
        {
            mDirectionalLight = make_shared<Light>(LightType::Directional);
            mDirectionalLight->mAmbient = Color(055, 055, 055);
            mDirectionalLight->mDiffuse = Color(055, 055, 055);
            mDirectionalLight->mSpecular = Color(055, 055, 055);
            mDirectionalLight->mDirection = Vector3f(1, 1, 1);
        }

        {
            mPointLight1->SetAmbient(ColorPalette::Gold);
            mPointLight1->SetDiffuse(Color(105, 105, 105));
            mPointLight1->SetSpecular(Color(105, 105, 105));
            mPointLight1->SetConstant(0.1f);
            mPointLight1->SetLinear(0.015f);
            mPointLight1->SetQuadratic(0.0075f);
            mPointLight1->SetPosition(Vector3f(-4.92804479598999, -6.6115264892578125, 3.654505729675293));
        }

        {
            mPointLight2->SetAmbient(ColorPalette::Gold);
            mPointLight2->SetDiffuse(Color(105, 105, 105));
            mPointLight2->SetSpecular(Color(105, 105, 105));
            mPointLight2->SetConstant(0.1f);
            mPointLight2->SetLinear(0.015f);
            mPointLight2->SetQuadratic(0.0075f);
            mPointLight2->SetPosition(Vector3f(5.09701681137085, -6.6115264892578125, 3.654505729675293));
        }

        {
            mPointLight3->SetAmbient(ColorPalette::Gold);
            mPointLight3->SetDiffuse(Color(105, 105, 105));
            mPointLight3->SetSpecular(Color(105, 105, 105));
            mPointLight3->SetConstant(0.1f);
            mPointLight3->SetLinear(0.015f);
            mPointLight3->SetQuadratic(0.0075f);
            mPointLight3->SetPosition(Vector3f(0.0, 0.0, 9.546284675598145));

        }

        mScenePointLightList = { mPointLight1->GetLight(), mPointLight2->GetLight(), mPointLight3->GetLight() };

        mRootNode = mRoom->GetNode();
        mRootNode->AttachChild(mPointLight1->GetNode());
        mRootNode->AttachChild(mPointLight2->GetNode());
        mRootNode->AttachChild(mPointLight3->GetNode());
        mSceneNode = make_shared<Node>();
        mSceneNode->mWorldTransform = Matrix4f::Zero;
        mSceneNode->AttachChild(mRootNode);

        mSceneLightingEffect = make_shared<PhongLightingEffect>();

        // Initialize Effect
        mSceneLightingEffect->CreateInstance(mSceneLightingEffect, mRoom->GetNode().get(), *mDirectionalLight, mScenePointLightList, mSceneSpotLightList);
    }

    // Initialize Interaction.
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
                             ColorPalette::Gold);
    }

    auto input = GameEngineInput::GetInstance();
    auto keyboard = input->GetKeyboardState();
    auto mouse = input->GetMouseState();

    // Draw Mouse
    {
        auto mousePositionDiff = mouse->GetPositionDiff();
        auto mousePosition = mouse->GetPosition();

        graphics->DrawString(mFont_Console, 16.f, Vector2f(50.f, height - 100.f),
                             "Mouse Position: " + to_string(mousePosition) + " Diff: " + to_string(mousePositionDiff), ColorPalette::White);
    }

    // Draw Camera
    {
        auto position = mCamera->GetPosition();
        graphics->DrawString(mFont_Console, 16.f, Vector2f(50.f, 50.f),
                             "Camera Position: " + to_string(position), ColorPalette::White);

        auto pitch = Degree(mCamera->mPitch);
        auto yaw = Degree(mCamera->mYaw);
        auto roll = Degree(mCamera->mRoll);
        graphics->DrawString(mFont_Console, 16.f, Vector2f(50.f, 100.f),
                             "Camera Pitch: " + std::to_string(pitch) + " Yaw: " + std::to_string(yaw) + " Roll: " + std::to_string(roll), ColorPalette::White);
    }

    graphics->Draw(mCamera.get(), mRoom.get());
    graphics->DrawBoundingBox(mCamera.get(), mPointLight1.get(), Transparent(ColorPalette::Yellow, 1.0f));
    graphics->DrawBoundingBox(mCamera.get(), mPointLight2.get(), Transparent(ColorPalette::Green, 1.0f));

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
