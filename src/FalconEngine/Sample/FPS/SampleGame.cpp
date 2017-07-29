#include "SampleGame.h"

#include <FalconEngine/Graphics/Effect/PaintEffect.h>

using namespace std;

namespace FalconEngine
{

SampleGame::SampleGame()
{
    mCamera = make_shared<FirstPersonCamera>(Coordinate::GetStandard(), HandednessRight::GetInstance());
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
            mRoomNode = ShareClone(roomModel->GetNode());
            sceneNode->AttachChild(mRoomNode);

            auto boxModel = assetManager->LoadModel("Content/Model/Engine/Box.dae");
            auto boxNode = boxModel->GetNode();
            mDirectionalLight = make_shared<LightEntity>(ShareClone(boxNode), LightType::Directional);
            mPointLight1 = make_shared<LightEntity>(ShareClone(boxNode), LightType::Point);
            mPointLight2 = make_shared<LightEntity>(ShareClone(boxNode), LightType::Point);
            mPointLight3 = make_shared<LightEntity>(ShareClone(boxNode), LightType::Point);
            mRoomNode->AttachChild(mPointLight1->GetNode());
            mRoomNode->AttachChild(mPointLight2->GetNode());
            mRoomNode->AttachChild(mPointLight3->GetNode());

            // Axis
            auto axeModel = assetManager->LoadModel("Content/Model/Engine/Axe.dae");
            auto axeNodeX = ShareClone(axeModel->GetNode());
            auto axeNodeY = ShareClone(axeModel->GetNode());
            auto axeNodeZ = ShareClone(axeModel->GetNode());
            auto axeNode = make_shared<Node>();
            axeNode->AttachChild(axeNodeX);
            axeNode->AttachChild(axeNodeY);
            axeNode->AttachChild(axeNodeZ);
            axeNodeX->mLocalTransform = Matrix4f::CreateRotationZ(-PiOver2);
            axeNodeY->mLocalTransform = Matrix4f::Identity;
            axeNodeZ->mLocalTransform = Matrix4f::CreateRotationX(+PiOver2);
            sceneNode->AttachChild(axeNode);

            auto sceneAxeEffect = make_shared<PaintEffect>();
            auto sceneAxeEffectParamX = make_shared<PaintEffectParams>(ColorPalette::Red);
            auto sceneAxeEffectParamY = make_shared<PaintEffectParams>(ColorPalette::Green);
            auto sceneAxeEffectParamZ = make_shared<PaintEffectParams>(ColorPalette::Blue);
            sceneAxeEffect->CreateInstance(axeNodeX.get(), sceneAxeEffectParamX);
            sceneAxeEffect->CreateInstance(axeNodeY.get(), sceneAxeEffectParamY);
            sceneAxeEffect->CreateInstance(axeNodeZ.get(), sceneAxeEffectParamZ);
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
        mSceneLightingEffect->CreateInstance(mRoomNode.get(), mSceneLightingParams);
    }

    // Initialize Interaction.
    {
        mCamera->LookAt(Vector3f(0, 0, 0), Vector3f(0, 0, -1), Vector3f::UnitY);

        static auto sDebugRenderer = DebugRenderer::GetInstance();
        sDebugRenderer->AddCamera(mCamera.get());
    }
}

void
SampleGame::Render(GameEngineGraphics *graphics, double percent)
{
    static auto sMasterRenderer = graphics->GetMasterRenderer();
    static auto sFontRenderer = graphics->GetFontRenderer();

    sMasterRenderer->ClearFrameBuffer(ColorPalette::Gray, 1.f, 0);

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

        sFontRenderer->DrawString(mFont, 16.f, Vector2f(50.f, height - 50.f),
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

        sFontRenderer->DrawString(mFont, 16.f, Vector2f(50.f, height - 100.f),
                                  "Mouse Position: " + to_string(mousePosition) + " Diff: " + to_string(mousePositionDiff), ColorPalette::White);
    }

    // Draw Camera
    {
        auto position = mCamera->GetPosition();
        sFontRenderer->DrawString(mFont, 16.f, Vector2f(50.f, 50.f),
                                  "Camera Position: " + to_string(position), ColorPalette::White);

        auto pitch = Degree(mCamera->mPitchRadian);
        auto yaw = Degree(mCamera->mYawRadian);
        auto roll = Degree(mCamera->mRollRadian);
        sFontRenderer->DrawString(mFont, 16.f, Vector2f(50.f, 100.f),
                                  "Camera Pitch: " + std::to_string(pitch) + " Yaw: " + std::to_string(yaw) + " Roll: " + std::to_string(roll), ColorPalette::White);
    }

    static auto sEntityRenderer = graphics->GetEntityRenderer();
    sEntityRenderer->Draw(mCamera.get(), mScene.get());

    Game::Render(graphics, percent);
}

void
SampleGame::Update(GameEngineGraphics *graphics, GameEngineInput *input, double elapsed)
{
    auto keyboard = input->GetKeyboardState();
    auto mouse = input->GetMouseState();

    if (keyboard->KeyPressed(Key::Escape))
    {
        GetEngine()->Exit();
    }

    mCamera->Update(input, elapsed);
    mScene->Update(input, elapsed);

    static auto sDebugRenderer = graphics->GetDebugRenderer();

    if (keyboard->KeyDown(Key::A))
    {
        sDebugRenderer->AddCircle(mCamera.get(), Vector3f(1, 0, 0), Vector3f::UnitX, 1.0f, ColorPalette::Red, 3.0f, false);
        sDebugRenderer->AddCircle(mCamera.get(), Vector3f(1, 0, 0), Vector3f::UnitY, 5.0f, ColorPalette::Red, 4.0f, false);
        sDebugRenderer->AddCircle(mCamera.get(), Vector3f(1, 0, 0), Vector3f::UnitZ, 7.0f, ColorPalette::Red, 5.0f, false);
    }
    // sDebugRenderer->AddAABB(mCamera.get(), mPointLight1.get(), Transparent(ColorPalette::Yellow, 1.0f), 0.0f, true);
    // sDebugRenderer->AddAABB(mCamera.get(), mPointLight2.get(), Transparent(ColorPalette::Green, 1.0f), 0.0f, true);

    Game::Update(graphics, input, elapsed);
}

}
