#include "SampleGame.h"

using namespace std;

namespace FalconEngine
{

SampleGame::SampleGame()
{
    mCamera = make_shared<FirstPersonCamera>(&mHandedness);
}

SampleGame::~SampleGame()
{
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
            mFont = assetManager->LoadFont("Content/Font/LuciadaConsoleDistanceField.fnt.bin").get();
            // mFont = mAssetManager->LoadFont("Content/Fonts/NSimSunDistanceField.fnt.bin").get();
        }

        // Entities
        {
            mScene = make_shared<SceneEntity>();

            auto sceneNode = mScene->GetNode();
            sceneNode->mWorldTransform = Matrix4f::Zero;

            auto roomModel = assetManager->LoadModel("Content/Model/Bedroom.dae");
            auto roomNode = ShareClone(roomModel->GetNode());
            sceneNode->AttachChild(roomNode);

            auto boxModel = assetManager->LoadModel("Content/Model/Engine/Box.dae");
            auto boxNode = boxModel->GetNode();
            mDirectionalLight = make_shared<LightEntity>(ShareClone(boxNode), LightType::Directional);
            mPointLight1 = make_shared<LightEntity>(ShareClone(boxNode), LightType::Point);
            mPointLight2 = make_shared<LightEntity>(ShareClone(boxNode), LightType::Point);
            mPointLight3 = make_shared<LightEntity>(ShareClone(boxNode), LightType::Point);
            roomNode->AttachChild(mPointLight1->GetNode());
            roomNode->AttachChild(mPointLight2->GetNode());
            roomNode->AttachChild(mPointLight3->GetNode());
        }
    }

    // Initialize Scene
    {
        {
            mDirectionalLight->SetAmbient(Color(055, 055, 055));
            mDirectionalLight->SetDiffuse(Color(055, 055, 055));
            mDirectionalLight->SetSpecular(Color(055, 055, 055));
            mDirectionalLight->SetDirection(Vector3f(1, 1, 1));
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

        // Initialize Effect
        mSceneLightingParams = make_shared<PhongEffectParams>();
        mSceneLightingParams->mDirectionalLight = mDirectionalLight->GetLight();
        mSceneLightingParams->mPointLightList = { mPointLight1->GetLight(), mPointLight2->GetLight(), mPointLight3->GetLight() };

        mSceneLightingEffect = make_shared<PhongEffect>();
        mSceneLightingEffect->CreateInstance(mScene->GetNode().get(), mSceneLightingParams);
    }

    // Initialize Interaction.
    {
        mCamera->LookAt(Vector3f(0, 0, 0), Vector3f(0, 0, -1), Vector3f::UnitY);
    }
}

void
SampleGame::Render(GameEngineGraphics *graphics, double percent)
{
    graphics->ClearFrameBuffer(ColorPalette::Gray, 1.f, 0);

    auto gameEngineSettings = GameEngineSettings::GetInstance();
    auto width  = gameEngineSettings->mWindowWidth;
    auto height = gameEngineSettings->mWindowHeight;

    // Draw Profiler
    {
        auto profiler = GameEngineProfiler::GetInstance();
        auto lastFrameFPS = int(profiler->GetLastFrameFps());
        auto lastUpdateElapsedMillisecond = int(profiler->GetLastUpdateElapsedMillisecond());
        auto lastFrameUpdateCount = int(profiler->GetLastFrameUpdateTotalCount());
        auto lastRenderElapsedMillisecond = int(profiler->GetLastRenderElapsedMillisecond());

        graphics->DrawString(mFont, 16.f, Vector2f(50.f, height - 50.f),
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

        graphics->DrawString(mFont, 16.f, Vector2f(50.f, height - 100.f),
                             "Mouse Position: " + to_string(mousePosition) + " Diff: " + to_string(mousePositionDiff), ColorPalette::White);
    }

    // Draw Camera
    {
        auto position = mCamera->GetPosition();
        graphics->DrawString(mFont, 16.f, Vector2f(50.f, 50.f),
                             "Camera Position: " + to_string(position), ColorPalette::White);

        auto pitch = Degree(mCamera->mPitchRadian);
        auto yaw = Degree(mCamera->mYawRadian);
        auto roll = Degree(mCamera->mRollRadian);
        graphics->DrawString(mFont, 16.f, Vector2f(50.f, 100.f),
                             "Camera Pitch: " + std::to_string(pitch) + " Yaw: " + std::to_string(yaw) + " Roll: " + std::to_string(roll), ColorPalette::White);
    }

    graphics->Draw(mCamera.get(), mScene.get());
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
    mScene->Update(input, elapsed);

    Game::Update(input, elapsed);
}

}
