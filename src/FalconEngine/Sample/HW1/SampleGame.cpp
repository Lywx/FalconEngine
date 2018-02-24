#include "SampleGame.h"

#include <FalconEngine/Graphics/Effect/PaintEffect.h>
#include <FalconEngine/Graphics/Effect/SkyEffect.h>

using namespace std;

namespace FalconEngine
{

SampleGame::SampleGame() :
    mBoxTheta(0),
    mMount(false)
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
#if defined(FALCON_ENGINE_DEBUG)
    GameEngineDebugger::GetInstance()->Initialize();
#endif

    // Load all assets.
    auto assetManager = AssetManager::GetInstance();

    // Fonts
    {
        mFont = assetManager->LoadFont("Content/Font/LuciadaConsoleDistanceField.fnt.bin").get();
    }

    // Entities
    {
        mScene = make_shared<SceneEntity>();
        auto sceneNode = mScene->GetNode();

        // Terrain
        {
            auto terrainModel = assetManager->LoadModel("Content/Model/SnowTerrain.dae");
            mTerrainNode = ShareClone(terrainModel->GetNodeSp());
            sceneNode->AttachChild(mTerrainNode);
        }

        // Light Source Indicator
        {
            auto boxModel = assetManager->LoadModel("Content/Model/Engine/Box.dae");
            auto boxNode = boxModel->GetNodeSp();
            mDirectionalLight = make_shared<LightEntity>(ShareClone(boxNode), LightType::Directional);
            mPointLight1 = make_shared<LightEntity>(ShareClone(boxNode), LightType::Point);
            mPointLight2 = make_shared<LightEntity>(ShareClone(boxNode), LightType::Point);
            mPointLight3 = make_shared<LightEntity>(ShareClone(boxNode), LightType::Point);
            mTerrainNode->AttachChild(mPointLight1->GetNodeSp());
            mTerrainNode->AttachChild(mPointLight2->GetNodeSp());
            mTerrainNode->AttachChild(mPointLight3->GetNodeSp());
        }

        // Axis Indicator
        {
            auto axeModel = assetManager->LoadModel("Content/Model/Engine/Axe.dae");
            auto axeNodeX = ShareClone(axeModel->GetNodeSp());
            auto axeNodeY = ShareClone(axeModel->GetNodeSp());
            auto axeNodeZ = ShareClone(axeModel->GetNodeSp());
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

        {
            auto boxModel = assetManager->LoadModel("Content/Model/Woodbox.dae");
            mBox = make_shared<SceneEntity>(ShareClone(boxModel->GetNodeSp()));
            mTerrainNode->AttachChild(mBox->GetNodeSp());
        }

        {
            auto snowballModel = assetManager->LoadModel("Content/Model/Snowball.dae");
            auto snowmanNodeBody = ShareClone(snowballModel->GetNodeSp());
            auto snowmanNodeHead = ShareClone(snowballModel->GetNodeSp());
            auto snowmanNode = make_shared<Node>();
            snowmanNode->AttachChild(snowmanNodeHead);
            snowmanNode->AttachChild(snowmanNodeBody);
            snowmanNodeHead->mLocalTransform = Matrix4f::CreateTranslation(0, 0, 2.5);
            snowmanNodeBody->mLocalTransform = Matrix4f::CreateScaleIsomorphic(2.0);
            mSnowman1 = make_shared<SceneEntity>(ShareClone(snowmanNode));
            mSnowman1->SetScale(Vector3f(0.5f, 0.5f, 0.5f));
            mSnowman1->SetPosition(Vector3f(5, 8, 2));
            mSnowman2 = make_shared<SceneEntity>(ShareClone(snowmanNode));
            mSnowman2->SetScale(Vector3f(0.5f, 0.5f, 0.5f));
            mSnowman2->SetPosition(Vector3f(0, 0, 2));
            mBox->GetNode()->AttachChild(mSnowman2->GetNodeSp());

            mTerrainNode->AttachChild(mSnowman1->GetNodeSp());
        }

        auto skydromeModel = assetManager->LoadModel("Content/Model/Skydrome.dae");
        mSkydromeNode = ShareClone(skydromeModel->GetNodeSp());
        mSkydromeNode->mLocalTransform = Matrix4f::CreateRotationZ(+PiOver2);
        mSkydromeNode->mWorldTransformIsCurrent = false;
        mSkydrome = std::make_shared<SceneEntity>(mSkydromeNode);
    }

    // Initialize Scene
    {
        {
            mDirectionalLight->SetAmbient(Color(45, 45, 45));
            mDirectionalLight->SetDiffuse(Color(225, 225, 225));
            mDirectionalLight->SetSpecular(Color(155, 155, 155));
            mDirectionalLight->SetDirection(Vector3f(1, 1, 1));
        }

        {
            mPointLight1->SetAmbient(ColorPalette::Gold);
            mPointLight1->SetDiffuse(Color(25, 25, 25));
            mPointLight1->SetSpecular(Color(15, 15, 15));
            mPointLight1->SetConstant(0.1f);
            mPointLight1->SetLinear(0.015f);
            mPointLight1->SetQuadratic(0.0075f);
            mPointLight1->SetPosition(Vector3f(-4.92804479598999, -15.6115264892578125, 3.654505729675293));
        }

        {
            mPointLight2->SetAmbient(ColorPalette::Gold);
            mPointLight2->SetDiffuse(Color(45, 45, 45));
            mPointLight2->SetSpecular(Color(15, 15, 15));
            mPointLight2->SetConstant(0.1f);
            mPointLight2->SetLinear(0.015f);
            mPointLight2->SetQuadratic(0.0075f);
            mPointLight2->SetPosition(Vector3f(9.09701681137085, -6.6115264892578125, 3.654505729675293));
        }

        {
            mPointLight3->SetAmbient(ColorPalette::Gold);
            mPointLight3->SetDiffuse(Color(65, 65, 65));
            mPointLight3->SetSpecular(Color(15, 15, 15));
            mPointLight3->SetConstant(0.1f);
            mPointLight3->SetLinear(0.015f);
            mPointLight3->SetQuadratic(0.0075f);
            mPointLight3->SetPosition(Vector3f(0.0, 0.0, 3.546284675598145));
        }

        // Initialize Effect
        mSceneLightingParams = make_shared<PhongEffectParams>();
        mSceneLightingParams->mDirectionalLight = mDirectionalLight->GetLight();
        mSceneLightingParams->mPointLightList = { mPointLight1->GetLight(), mPointLight2->GetLight(), mPointLight3->GetLight() };

        mSceneLightingEffect = make_shared<PhongEffect>();
        mSceneLightingEffect->CreateInstance(mTerrainNode.get(), mSceneLightingParams);

        mSceneSkyParams = make_shared<SkyEffectParams>();
        mSceneSkyEffect = make_shared<SkyEffect>();
        mSceneSkyEffect->CreateInstance(mSkydromeNode.get(), mSceneSkyParams);
    }

    // Initialize Interaction.
    {
        mCamera->LookAt(Vector3f(30, 3, 10), Vector3f::Zero, Vector3f::UnitY);

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
    auto width  = gameEngineSettings->mWindowWidth;
    auto height = gameEngineSettings->mWindowHeight;

    // Draw Profiler
    {
        auto profiler = GameEngineProfiler::GetInstance();
        auto lastFrameFPS = int(profiler->GetLastFrameFps());
        auto lastUpdateElapsedMillisecond = int(profiler->GetLastUpdateElapsedMillisecond());
        auto lastFrameUpdateCount = int(profiler->GetLastFrameUpdateTotalCount());
        auto lastRenderElapsedMillisecond = int(profiler->GetLastRenderElapsedMillisecond());

        sFontRenderer->AddText(mFont, 12.f, Vector2f(50.f, height - 50.f),
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

        sFontRenderer->AddText(mFont, 12.f, Vector2f(50.f, height - 100.f),
                               "Mouse Position: " + to_string(mousePosition) + " Diff: " + to_string(mousePositionDiff), ColorPalette::White);
    }

    // Draw Camera
    {
        auto position = mCamera->GetPosition();
        sFontRenderer->AddText(mFont, 12.f, Vector2f(50.f, 50.f),
                               "Camera Position: " + to_string(position), ColorPalette::White);

        auto pitch = Degree(mCamera->mPitchRadian);
        auto yaw = Degree(mCamera->mYawRadian);
        auto roll = Degree(mCamera->mRollRadian);
        sFontRenderer->AddText(mFont, 12.f, Vector2f(50.f, 100.f),
                               "Camera Pitch: " + std::to_string(pitch) + " Yaw: " + std::to_string(yaw) + " Roll: " + std::to_string(roll), ColorPalette::White);
    }

    {
        sFontRenderer->AddText(mFont, 12.f, Vector2f(50.f, 150.f),
                               "Press Keyboard Key O - Create AABB in camera position for lasting 4 seconds.", ColorPalette::White);

        sFontRenderer->AddText(mFont, 12.f, Vector2f(50.f, 200.f),
                               "Press Keyboard Key I - Key Press Testing", ColorPalette::White);

        sFontRenderer->AddText(mFont, 12.f, Vector2f(50.f, 250.f),
                               "Press Mouse Left Button - Mouse Press Testing", ColorPalette::White);

        sFontRenderer->AddText(mFont, 12.f, Vector2f(50.f, 600.f),
                               "Press Keyboard Key E - Unmount from the box", ColorPalette::Gold);
    }

    // Draw Scene.
    static auto sEntityRenderer = graphics->GetEntityRenderer();
    sEntityRenderer->Draw(mCamera.get(), mSkydrome.get());
    sEntityRenderer->Draw(mCamera.get(), mScene.get());

    Game::Render(graphics, percent);
}

bool
SampleGame::BadCollisionTest(const Node *node)
{
    auto slotNum = node->GetChildrenSlotNum();
    auto cpos = mCamera->GetPosition();

    for (auto slotIndex = 0; slotIndex < slotNum; ++slotIndex)
    {
        auto child = node->GetChildAt(slotIndex);
        if (auto visual = dynamic_cast<const Visual *>(child))
        {
            auto aabb = visual->GetMesh()->GetAabb();
            auto max = Vector3f(visual->mWorldTransform * Vector4f(aabb->mMax, 1));
            auto min = Vector3f(visual->mWorldTransform * Vector4f(aabb->mMin, 1));

            // HACK(Wuxiang): Having trouble detecting collision.
            if (cpos.x < max.x
                    && cpos.y < max.y
                    && cpos.z < max.z
                    && cpos.x > min.x
                    //&& cpos.y > min.y
                    //&& cpos.z > min.z
               )
            {
                return true;
            }
        }
        else if (auto childNode = dynamic_cast<const Node *>(child))
        {
            if (BadCollisionTest(childNode))
            {
                return true;
            }
        }
    }

    return false;
}

void
SampleGame::Update(GameEngineGraphics *graphics, GameEngineInput *input, double elapsed)
{
    // Box movement
    auto radius = 5;
    mBoxTheta += 2 * elapsed / 1000;
    mBox->SetPosition(Vector3f(cos(mBoxTheta) * radius, sin(mBoxTheta) * radius, 2));

    mSkydrome->Update(input, elapsed);
    mScene->Update(input, elapsed);

    if (mMount)
    {
        auto transform = mBox->GetNode()->mWorldTransform;
        mCamera->SetPosition(Vector3f(transform[3][0], transform[3][1] + 6, transform[3][2]));
    }

    mCamera->Update(input, elapsed);

    Game::Update(graphics, input, elapsed);
}

void
SampleGame::UpdateFrame(GameEngineGraphics *graphics, GameEngineInput *input, double elasped)
{
    auto keyboard = input->GetKeyboardState();
    auto mouse = input->GetMouseState();

    if (keyboard->KeyPressed(Key::Escape))
    {
        GetEngine()->Exit();
    }

    // Input testing
    static auto sDebugRenderer = graphics->GetDebugRenderer();
    if (keyboard->KeyPressed(Key::I))
    {
        sDebugRenderer->AddText("Key I is pressed.", Vector2f(50.0f, 500.0f), 12.0f, ColorPalette::Gold, 0.0f);
    }

    if (mouse->ButtonPressed(MouseButton::LeftButton))
    {
        sDebugRenderer->AddText("Left Button is pressed.", Vector2f(50.0f, 550.0f), 12.0f, ColorPalette::Gold, 0.0f);
    }

    if (keyboard->KeyPressed(Key::O))
    {
        sDebugRenderer->AddAabb(mCamera->GetPosition() + Vector3f(-1, -1, -1), mCamera->GetPosition() + Vector3f(1, 1, 1), Transparent(ColorPalette::Yellow, 1.0f), 4.0f, true);
    }

    if (keyboard->KeyPressed(Key::E))
    {
        mMount = false;
    }

    // Collision indicator
    sDebugRenderer->AddAabb(mBox.get(), Transparent(ColorPalette::Red, 1.0f), 0.0f, true);

    // Light source indicator
    sDebugRenderer->AddAabb(mPointLight1.get(), Transparent(ColorPalette::Red, 1.0f), 0.0f, true);
    sDebugRenderer->AddAabb(mPointLight2.get(), Transparent(ColorPalette::Red, 1.0f), 0.0f, true);
    sDebugRenderer->AddAabb(mPointLight3.get(), Transparent(ColorPalette::Red, 1.0f), 0.0f, true);

    if (BadCollisionTest(mBox->GetNode()))
    {
        sDebugRenderer->AddText("Collision detected.", Vector2f(50.0f, 650.0f), 12.0f, ColorPalette::Gold, 1.0f);
        mMount = true;
    }

    Game::UpdateFrame(graphics, input, elasped);
}

}
