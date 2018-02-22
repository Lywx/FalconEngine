#include "SampleGame.h"

#include <FalconEngine/Graphics/Effect/BlinnEffect.h>
#include <FalconEngine/Graphics/Effect/PaintEffect.h>
#include <FalconEngine/Graphics/Effect/PhongEffect.h>
#include <FalconEngine/Graphics/Effect/MeshEffect.h>

using namespace std;

namespace FalconEngine
{

SampleGame::SampleGame()
{
    mCamera = make_shared<ThirdPersonCamera>(Coordinate::GetStandard(), HandednessRight::GetInstance());
}

SampleGame::~SampleGame()
{
}

void
SampleGame::Initialize()
{
    // Initialize debug context.
#if defined(FALCON_ENGINE_DEBUG)
    GameEngineDebugger::GetInstance()->Initialize();
#endif

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
            auto sceneNode = mScene->GetNodeSp();
            sceneNode->mWorldTransform = Matrix4f::Zero;

            // Room
            auto roomModel = assetManager->LoadModel("Content/Model/Bedroom.dae");
            mRoomNode = ShareClone(roomModel->GetNodeSp());
            sceneNode->AttachChild(mRoomNode);

            // Light
            auto boxModel = assetManager->LoadModel("Content/Model/Engine/Box.dae");
            auto boxNode = boxModel->GetNodeSp();
            mDirectionalLight = make_shared<LightEntity>(ShareClone(boxNode), LightType::Directional);
            mPointLight1 = make_shared<LightEntity>(ShareClone(boxNode), LightType::Point);
            mPointLight2 = make_shared<LightEntity>(ShareClone(boxNode), LightType::Point);
            mPointLight3 = make_shared<LightEntity>(ShareClone(boxNode), LightType::Point);
            mRoomNode->AttachChild(mPointLight1->GetNodeSp());
            mRoomNode->AttachChild(mPointLight2->GetNodeSp());
            mRoomNode->AttachChild(mPointLight3->GetNodeSp());

            // Axis
            auto axeModel = assetManager->LoadModel("Content/Model/Engine/Axe.dae");
            auto axeNodeX = ShareClone(axeModel->GetNodeSp());
            auto axeNodeY = ShareClone(axeModel->GetNodeSp());
            auto axeNodeZ = ShareClone(axeModel->GetNodeSp());
            mAxeNode = make_shared<Node>();
            mAxeNode->AttachChild(axeNodeX);
            mAxeNode->AttachChild(axeNodeY);
            mAxeNode->AttachChild(axeNodeZ);
            axeNodeX->mLocalTransform = Matrix4f::CreateRotationZ(-PiOver2);
            axeNodeY->mLocalTransform = Matrix4f::Identity;
            axeNodeZ->mLocalTransform = Matrix4f::CreateRotationX(+PiOver2);
            sceneNode->AttachChild(mAxeNode);

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
        mCamera->SetTarget(Vector3f(0, 0, 0));
        mCamera->mAzimuthalRadian = Radian(40.0f);
        mCamera->mPolarRadian = Radian(40.0f);
        mCamera->mRadialDistance = 40.0f;

        static auto sDebugRenderer = DebugRenderer::GetInstance();
        sDebugRenderer->SetCamera(mCamera.get());
    }
}

void
SampleGame::Render(GameEngineGraphics *graphics, double percent)
{
    static auto sMasterRenderer = graphics->GetMasterRenderer();
    static auto sFontRenderer = graphics->GetFontRenderer();

    sMasterRenderer->ClearFrameBuffer(ColorPalette::Gray, 1.f, 0);

    auto gameEngineSettings = GameEngineSettings::GetInstance();

    // Draw Profiler
    {
        auto profiler = GameEngineProfiler::GetInstance();
        auto lastFrameFPS = int(profiler->GetLastFrameFps());
        auto lastUpdateElapsedMillisecond = int(profiler->GetLastUpdateElapsedMillisecond());
        auto lastFrameUpdateCount = int(profiler->GetLastFrameUpdateTotalCount());
        auto lastRenderElapsedMillisecond = int(profiler->GetLastRenderElapsedMillisecond());

        sFontRenderer->AddText(mFont, 16.f, Vector2f(50.f, gameEngineSettings->mWindowHeight - 50.f),
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

        sFontRenderer->AddText(mFont, 16.f, Vector2f(50.f, gameEngineSettings->mWindowHeight - 100.f),
                               "Mouse Position: " + to_string(mousePosition) + " Diff: " + to_string(mousePositionDiff), ColorPalette::White);
    }

    // Draw Camera
    {
        auto position = mCamera->GetPosition();
        sFontRenderer->AddText(mFont, 16.f, Vector2f(50.f, 50.f),
                               "Camera Position: " + to_string(position), ColorPalette::White);

        auto theta = Degree(mCamera->mAzimuthalRadian);
        auto phi = Degree(mCamera->mPolarRadian);
        auto distance = Degree(mCamera->mRadialDistance);
        sFontRenderer->AddText(mFont, 16.f, Vector2f(50.f, 100.f),
                               "Camera Theta: " + std::to_string(theta) + " Phi: " + std::to_string(phi) + " Distance: " + std::to_string(distance), ColorPalette::White);
    }

    static auto sEntityRenderer = graphics->GetEntityRenderer();
    sEntityRenderer->Draw(mCamera.get(), mScene.get());

    static auto sDebugRenderer = graphics->GetDebugRenderer();
    sDebugRenderer->AddAabb(mPointLight1.get(), Transparent(ColorPalette::Yellow, 1.0f));
    sDebugRenderer->AddAabb(mPointLight2.get(), Transparent(ColorPalette::Green, 1.0f));

    sFontRenderer->AddText(mFont, 16.0f, Vector2f(gameEngineSettings->mWindowWidth / 2.0f, gameEngineSettings->mWindowHeight / 2.0f), ".");

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

    Game::Update(graphics, input, elapsed);
}

}
